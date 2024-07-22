/*
    This file is part of the implementation of the SIGGRAPH 2020 paper
    "Robust Fitting of Parallax-Aware Mixtures for Path Guiding".
    The implementation extends Mitsuba, a physically based rendering system.

    Copyright (c) 2020 Lukas Ruppert, Sebastian Herholz.

    Mitsuba is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    Mitsuba is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <mitsuba/render/sampler.h>

MTS_NAMESPACE_BEGIN

/*!\plugin{deterministic}{Deterministic sampler}
 * \order{1}
 * \parameters{
 *     \parameter{sampleCount}{\Integer}{
 *       Number of samples per pixel \default{4}
 *     }
 * }
 *
 * The deterministic sampler allows to generate the same image
 * each time it is rendered.
 * This reproducibility is useful for debugging
 * but not so much for production.
 */
class DeterministicSampler : public Sampler {
public:
    DeterministicSampler() : Sampler(Properties()) { }

    DeterministicSampler(const Properties &props) : Sampler(props) {
        /* Number of samples per pixel when used with a sampling-based integrator */
        m_sampleCount = props.getSize("sampleCount", 4);
        m_salt = props.getSize("salt", 0);
        m_seed = props.getSize("seed", 0);
        m_random = new Random(m_seed);
    }

    DeterministicSampler(Stream *stream, InstanceManager *manager)
     : Sampler(stream, manager) {
        m_random = static_cast<Random *>(manager->getInstance(stream));
        m_seed = stream->readULong();
        m_salt = stream->readULong();
    }

    void serialize(Stream *stream, InstanceManager *manager) const {
        Sampler::serialize(stream, manager);
        manager->serialize(stream, m_random.get());
        stream->writeULong(m_seed);
        stream->writeULong(m_salt);
    }

    ref<Sampler> clone() {
        ref<DeterministicSampler> sampler = new DeterministicSampler();
        sampler->m_sampleCount = m_sampleCount;
        sampler->m_seed = m_seed;
        sampler->m_salt = m_salt;
        sampler->m_random = new Random(m_seed);
        for (size_t i=0; i<m_req1D.size(); ++i)
            sampler->request1DArray(m_req1D[i]);
        for (size_t i=0; i<m_req2D.size(); ++i)
            sampler->request2DArray(m_req2D[i]);
        return sampler.get();
    }

    void generate(const Point2i &p) {
        m_seed = (static_cast<uint64_t>(p.x)+(static_cast<uint64_t>(p.y)<<16))*(m_sampleCount+m_salt);
        m_random->seed(m_seed);

        for (size_t i=0; i<m_req1D.size(); i++)
            for (size_t j=0; j<m_sampleCount * m_req1D[i]; ++j)
                m_sampleArrays1D[i][j] = m_random->nextFloat();
        for (size_t i=0; i<m_req2D.size(); i++)
            for (size_t j=0; j<m_sampleCount * m_req2D[i]; ++j)
                m_sampleArrays2D[i][j] = Point2(
                    m_random->nextFloat(),
                    m_random->nextFloat());
        m_sampleIndex = 0;
        m_dimension1DArray = m_dimension2DArray = 0;
    }

    void advance() {
        m_sampleIndex++;

        //would only be necessary if one wanted to re-render individual paths
        //m_random->seed(++m_seed);

        for (size_t i=0; i<m_req1D.size(); i++)
            for (size_t j=0; j<m_sampleCount * m_req1D[i]; ++j)
                m_sampleArrays1D[i][j] = m_random->nextFloat();
        for (size_t i=0; i<m_req2D.size(); i++)
            for (size_t j=0; j<m_sampleCount * m_req2D[i]; ++j)
                m_sampleArrays2D[i][j] = Point2(
                    m_random->nextFloat(),
                    m_random->nextFloat());
    }

    Float next1D() {
        return m_random->nextFloat();
    }

    Point2 next2D() {
        Float value1 = m_random->nextFloat();
        Float value2 = m_random->nextFloat();
        return Point2(value1, value2);
    }

    void setSampleIndex(size_t sampleIndex) {
        if (sampleIndex > m_sampleCount)
        {
            m_salt = sampleIndex/m_sampleCount;
            sampleIndex = sampleIndex%m_sampleCount;
        }
        Sampler::setSampleIndex(sampleIndex);
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << "DeterministicSampler[" << endl
            << "  sampleCount = " << m_sampleCount << endl
            << "]";
        return oss.str();
    }

    MTS_DECLARE_CLASS()
private:
    ref<Random> m_random;
    uint64_t m_seed;
    uint64_t m_salt;
};

MTS_IMPLEMENT_CLASS_S(DeterministicSampler, false, Sampler)
MTS_EXPORT_PLUGIN(DeterministicSampler, "Deterministic sampler");
MTS_NAMESPACE_END
