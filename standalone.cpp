#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <iomanip>
#include <complex>
#include <array>
#include <fstream>
#include <sstream>
#pragma comment(linker, "/STACK:20000000") // avoid stack overflow

// make these larger for TT
const int N_DEGREE = 16; 
const int N_POLY = 128;

const int N_MAT = N_DEGREE + 1;

int perf_count = 0;

int cnt = 0;

class UnivariatePolynomial
{
public:
    UnivariatePolynomial(const std::vector<double> &c) : size(c.size())
    {
        for (int i = 0; i < c.size(); i++)
            coeffs[i] = c[i];
    }

    explicit UnivariatePolynomial(int s) : size(s)
    {
        for (int i = 0; i < s; i++)
            coeffs[i] = 0;
    }

    UnivariatePolynomial(int s, double c) : size(s)
    {
        for (int i = 0; i < s; i++)
            coeffs[i] = c;
    }

    std::string toScientificNotationWithPrecision(double value, int precision) const
    {
        std::ostringstream oss;
        oss << std::scientific << std::setprecision(precision) << value;
        return oss.str();
    }

    std::string toString() const
    {
        std::string result;
        size_t nonzero_count = 0;
        for (size_t i = 0; i < size; ++i)
        {
            double coeff = coeffs[i];
            result += toScientificNotationWithPrecision(coeff, 6);
            result += ", ";
        }
        if (!result.empty())
        {
            result.pop_back();
            result.pop_back();
            result.pop_back();
        }
        return result;
    }

    void print() const 
    {
        for (size_t i = 0; i < size; ++i)
        {
            double coeff = coeffs[i];
            if (coeff) {
                std::cout << coeff << ", ";
            }
        }
    }

    void printCoefficientsMatrix() const
    {
        size_t cols = size;

        std::cout << "Coefficients Matrix:" << std::endl;

        std::cout << "+";
        for (size_t j = 0; j < cols; ++j)
            std::cout << std::setw(12) << "+";
        std::cout << std::endl;

        std::cout << "|";
        for (size_t j = 0; j < cols; ++j)
            std::cout << std::setw(12) << coeffs[j];
        std::cout << "|" << std::endl;

        std::cout << "+";
        for (size_t j = 0; j < cols; ++j)
            std::cout << std::setw(12) << "+";
        std::cout << std::endl;
    }

    UnivariatePolynomial operator+(const UnivariatePolynomial &other) const
    {
        size_t max_cols = std::max(size, other.size);
        double padded_coeffs_this[N_POLY];
        double padded_coeffs_other[N_POLY];

        for (size_t j = 0; j < max_cols; ++j)
            padded_coeffs_this[j] = 0,
            padded_coeffs_other[j] = 0;
        for (size_t j = 0; j < size; ++j)
            padded_coeffs_this[j] = coeffs[j];
        for (size_t j = 0; j < other.size; ++j)
            padded_coeffs_other[j] = other.coeffs[j];
        UnivariatePolynomial sum(max_cols);
        for (size_t j = 0; j < max_cols; ++j)
            sum.coeffs[j] = padded_coeffs_this[j] + padded_coeffs_other[j];

        return sum;
    }

    UnivariatePolynomial operator*(const UnivariatePolynomial &other) const
    {
        size_t result_size = size + other.size - 1;
        UnivariatePolynomial result(result_size);

        for (size_t i = 0; i < size; ++i)
            for (size_t j = 0; j < other.size; ++j)
            {
                if (i + j >= N_POLY)
                    break;
                result.coeffs[i + j] += coeffs[i] * other.coeffs[j];
                cnt++;
            }

        return result;
    }

    UnivariatePolynomial operator*(double other) const
    {
        UnivariatePolynomial sum(size);
        for (size_t j = 0; j < size; ++j)
            sum.coeffs[j] = coeffs[j] * other;
        return sum;
    }

    UnivariatePolynomial operator-(const UnivariatePolynomial &other) const
    {
        return *this + (other * UnivariatePolynomial(1, -1));
    }

    void resize(size_t max_cols)
    {
        for (int i = size; i < max_cols; i++)
            coeffs[i] = 0;
        size = max_cols;
    }

    double evaluateAtU(double x) const
    {
        double result = 0.0;
        for (int i = size - 1; i >= 0; --i)
            result = result * x + coeffs[i];
        return result;
    }

    std::vector<double> getCoeffs() const
    {
        std::vector<double> v(size);
        for (int i = 0; i < size; i++)
            v[i] = coeffs[i];
        return v;
    }

    void normalize()
    {
        double mc = 1e-99;
        for (int i = -2 + size; i >= 1; i--)
            mc = std::max(mc, coeffs[i]);
        for (int i = -2 + size; i >= 0; i--)
            coeffs[i] /= mc;
    }

public:
    int size = 0; // size means the length = degree + 1
    double coeffs[N_POLY] = {};
};

class BivariatePolynomial
{
public:
    BivariatePolynomial(const std::vector<std::vector<double>> &c) : size(c.size())
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                coeffs[i][j] = c[i][j];
    }

    explicit BivariatePolynomial(int sz) : size(sz)
    {
    }

    BivariatePolynomial(int sz, double f) : size(sz)
    {
        coeffs[0][0] = f;
    }

    BivariatePolynomial() : size(0)
    {
    }

    std::string toScientificNotationWithPrecision(double value, int precision) const
    {
        std::ostringstream oss;
        oss << std::scientific << std::setprecision(precision) << value;
        return oss.str();
    }

    std::string toString() const
    {
        std::string result;
        for (size_t i = 0; i < size; ++i)
            for (size_t j = 0; j < size; ++j)
            {
                double coeff = coeffs[i][j];
                if (coeff != 0)
                {
                    result += toScientificNotationWithPrecision(coeff, 8);
                    if (i)
                        result += "*u.^" + std::to_string(i);
                    if (j)
                        result += "*v.^" + std::to_string(j);
                    result += " + ";
                }
            }
        if (!result.empty())
        {
            result.pop_back();
            result.pop_back();
            result.pop_back();
        }
        return result;
    }

    void printCoefficientsMatrix() const
    {
        size_t rows = size;
        size_t cols = size;

        std::cout << "Coefficients Matrix:" << std::endl;

        std::cout << "+";
        for (size_t j = 0; j < cols; ++j)
            std::cout << std::setw(12) << "+";
        std::cout << std::endl;

        for (size_t i = 0; i < rows; ++i)
        {
            std::cout << "|";
            for (size_t j = 0; j < cols; ++j)
                std::cout << std::setw(12) << coeffs[i][j];
            std::cout << "|" << std::endl;
        }

        std::cout << "+";
        for (size_t j = 0; j < cols; ++j)
            std::cout << std::setw(12) << "+";
        std::cout << std::endl;
    }

    BivariatePolynomial operator+(const BivariatePolynomial &other) const
    {
        BivariatePolynomial sum(std::max(size, other.size));
        for (size_t i = 0; i < sum.size; ++i)
            for (size_t j = 0; j < sum.size; ++j)
                sum.coeffs[i][j] = coeffs[i][j] + other.coeffs[i][j];
        return sum;
    }

    BivariatePolynomial operator*(const BivariatePolynomial &other) const
    {
        // ! we assume it is an upper triangle
        BivariatePolynomial result(std::min(N_MAT, size + other.size - 1));
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t k = 0; k < other.size && i + k < N_MAT; ++k)
            {
                for (size_t j = 0; i + j < size; ++j)
                {
                    for (size_t l = 0; k + l < other.size && j + l < N_MAT; ++l)
                    {
                        result.coeffs[i + k][j + l] += coeffs[i][j] * other.coeffs[k][l];
                    }
                }
            }
        }
        return result;
    }

    BivariatePolynomial scalarMul(double other) const
    {
        BivariatePolynomial result(std::max(size, 1));
        for (size_t i = 0; i < size; ++i)
            for (size_t j = 0; j < size; ++j)
                result.coeffs[i][j] = coeffs[i][j] * other;
        return result;
    }

    // todo: optimize
    BivariatePolynomial operator-(const BivariatePolynomial &other) const
    {
        return *this + (other.scalarMul(-1));
    }

    BivariatePolynomial operator-(double other) const
    {
        return *this + (BivariatePolynomial(1, other).scalarMul(-1));
    }

    void resize(size_t max_rows, size_t max_cols)
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (i >= max_rows || j >= max_rows)
                    coeffs[i][j] = 0;
        size = max_rows;
    }

    UnivariatePolynomial evaluateAtU(double value) const
    {
        std::vector<double> univariate_coeffs(size, 0);
        double pw = 1; // = value^i
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < size; ++j)
                univariate_coeffs[j] += coeffs[i][j] * pw;
            pw *= value;
        }
        return UnivariatePolynomial(univariate_coeffs);
    }

    UnivariatePolynomial evaluateAtV(double value) const
    {
        std::vector<double> univariate_coeffs(size, 0);
        for (size_t i = 0; i < size; ++i)
        {
            double pw = 1;
            for (size_t j = 0; j < size; ++j)
            {
                univariate_coeffs[i] += coeffs[i][j] * pw;
                pw *= value;
            }
        }
        return UnivariatePolynomial(univariate_coeffs);
    }

    std::vector<UnivariatePolynomial> toUnivariatePolynomials() const
    {
        // ! assume it is an upper triangle
        std::vector<UnivariatePolynomial> univariatePolys;
        int n = size;
        for (int i = 0; i < n; ++i)
        {
            std::vector<double> coefficients(n - i);
            for (int j = 0; j < n - i; ++j)
                coefficients[j] = coeffs[i][j];
            univariatePolys.push_back(UnivariatePolynomial(coefficients));
        }
        return univariatePolys;
    }

public:
    double coeffs[N_MAT + 1][N_MAT + 1] = {};
    int size; // size = length = maxdeg + 1
};

typedef std::vector<std::vector<UnivariatePolynomial>> UnivariatePolynomialMatrix;

void printUnivariatePolynomial(const UnivariatePolynomial &poly)
{
    poly.print();
}

void printUnivariatePolynomialMatrix(const UnivariatePolynomialMatrix &matrix)
{
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            matrix[i][j].print();
        }
    }
    std::cout << std::endl;
}

typedef BivariatePolynomial BVP;

struct BVP3
{
    BivariatePolynomial bvp[3];

    BVP3(const BivariatePolynomial &x, const BivariatePolynomial &y, const BivariatePolynomial &z) : bvp{x, y, z}
    {
    }

    BVP3 operator+(const BVP3 &rhs) const
    {
        return {bvp[0] + rhs.bvp[0], bvp[1] + rhs.bvp[1], bvp[2] + rhs.bvp[2]};
    }

    BVP3 operator-(const BVP3 &rhs) const
    {
        return {bvp[0] - rhs.bvp[0], bvp[1] - rhs.bvp[1], bvp[2] - rhs.bvp[2]};
    }

    BVP3 operator*(const BVP3 &rhs) const
    { // element-wise product
        return {bvp[0] * rhs.bvp[0], bvp[1] * rhs.bvp[1], bvp[2] * rhs.bvp[2]};
    }

    BVP3 operator+(const BivariatePolynomial &rhs) const
    {
        return {bvp[0] + rhs, bvp[1] + rhs, bvp[2] + rhs};
    }

    BVP3 operator-(const BivariatePolynomial &rhs) const
    {
        return {bvp[0] - rhs, bvp[1] - rhs, bvp[2] - rhs};
    }

    BVP3 operator*(const BivariatePolynomial &rhs) const
    {
        return {bvp[0] * rhs, bvp[1] * rhs, bvp[2] * rhs};
    }

    BivariatePolynomial dot(const BVP3 &rhs) const
    { // dot product
        return bvp[0] * rhs.bvp[0] + bvp[1] * rhs.bvp[1] + bvp[2] * rhs.bvp[2];
    }

    BVP3 cross(const BVP3 &rhs) const
    { // cross product
        return {bvp[1] * rhs.bvp[2] - bvp[2] * rhs.bvp[1], bvp[2] * rhs.bvp[0] - bvp[0] * rhs.bvp[2], bvp[0] * rhs.bvp[1] - bvp[1] * rhs.bvp[0]};
    }
};

UnivariatePolynomialMatrix bezout_matrix(const std::vector<UnivariatePolynomial> &a, const std::vector<UnivariatePolynomial> &b)
{
    size_t n = a.size() - 1;
    UnivariatePolynomialMatrix f(n, std::vector<UnivariatePolynomial>(n, UnivariatePolynomial({0})));
    for (size_t i = 0; i < n; ++i)
        for (size_t j = i; j < n; ++j)
            f[i][j] = a[i] * b[j + 1] - b[i] * a[j + 1];
    for (size_t i = 1; i < n - 1; ++i)
        for (size_t j = i; j < n - 1; ++j)
            f[i][j] = f[i][j] + f[i - 1][j + 1];
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < i; ++j)
            f[i][j] = f[j][i];

    return f;
}

int main()
{
    //////////////////////////////////////////////////
    // Choose a test case (please select one)

    // Test case for R #1
    // double ans_alpha = 0.109817;
    // double ans_u = 0.409893;

    // std::vector<double> pD_ = {0, 2.6, 1.1};
    // std::vector<double> pL_ = {1, 2.5, 2};
    // std::vector<double> p10_ = {-1.07752, 0.073294, -1.0518};
    // std::vector<double> n10_ = {-0.111471, 0.096233, 0.989097};
    // std::vector<double> p11_ = {0.030847, -0.002331, 0.00513101};
    // std::vector<double> n11_ = {0.453673, 0.306021, -1.83827};
    // std::vector<double> p12_ = {-1.07288e-06, 0.03624, -0.0257159};
    // std::vector<double> n12_ = {0.13615, 0.015406, 0.004345};
    // std::vector<double> p20_ = {0, 1, 0};
    // std::vector<double> n20_ = {0, 1, 0};
    // std::vector<double> p21_ = {0, 1, 0};
    // std::vector<double> n21_ = {0, 1, 0};
    // std::vector<double> p22_ = {0, 1, 0};
    // std::vector<double> n22_ = {0, 1, 0};

    // Test case for R #2
    // double ans_alpha = 0.671860456466675;
    // double ans_u = 0.083107322454453;
    // std::vector<double> pD_ = {0.0, 0.0, 10.0};
    // std::vector<double> pL_ = {0.0, 0.0, 9.999};
    // std::vector<double> p10_ = {0.156250000000000, -0.515625000000000, 0.000400904595153};
    // std::vector<double> n10_ = {-0.033636242151260, 0.020228719338775, 0.999229431152344};
    // std::vector<double> p11_ = {0.007812500000000, 0.007812500000000, -0.000963313155808};
    // std::vector<double> n11_ = {0.126469522714615, 0.127072423696518, -0.014503896236420};
    // std::vector<double> p12_ = {0.007812500000000, 0.000000000000000, 0.000249680160778};
    // std::vector<double> n12_ = {0.029931440949440, 0.084055192768574, -0.004688739776611};
    // std::vector<double> p20_ = {0, 1, 0};
    // std::vector<double> n20_ = {0, 1, 0};
    // std::vector<double> p21_ = {0, 1, 0};
    // std::vector<double> n21_ = {0, 1, 0};
    // std::vector<double> p22_ = {0, 1, 0};
    // std::vector<double> n22_ = {0, 1, 0};

    // Test case for T #1
    // double ans_alpha = 0.310013;
    // double ans_u = 0.301126;
    // std::vector<double> pD_ = {0, -2.6, -1.1};
    // std::vector<double> pL_ = {1, 2.5, 2};
    // std::vector<double> p10_ = {-0.933849, 0.091093, -1.07752};
    // std::vector<double> n10_ = {-0.80496, 0.081929, 0.587645};
    // std::vector<double> p11_ = {-0.025211, -0.021542, 0.0107059};
    // std::vector<double> n11_ = {-0.048272, 0.020128, -1.09909};
    // std::vector<double> p12_ = {-0.023945, -0.022294, 0.011972};
    // std::vector<double> n12_ = {1.71536, 0.1286, -0.943807};
    // std::vector<double> p20_ = {0, 1, 0};
    // std::vector<double> n20_ = {0, 1, 0};
    // std::vector<double> p21_ = {0, 1, 0};
    // std::vector<double> n21_ = {0, 1, 0};
    // std::vector<double> p22_ = {0, 1, 0};
    // std::vector<double> n22_ = {0, 1, 0};

    // Test case for RR #1
    double ans_alpha = 0.597033858299255;
    double ans_u = 0.211711958050728;
    std::vector<double> pD_ = {0, 2.6, 1.1};
    std::vector<double> pL_ = {0.01, 5, 0.01};
    std::vector<double> p10_ = {0.370296001434326, 0.626675009727478, 0.895971000194550};
    std::vector<double> n10_ = {0.788752138614655, 0.535826086997986, -0.301265031099319};
    std::vector<double> p11_ = {0.143369972705841, -0.233456015586853, -0.039860010147095};
    std::vector<double> n11_ = {0.019750535488129, -0.004185259342194, 0.048913121223450};
    std::vector<double> p12_ = {-0.027851998806000, 0.006330966949463, -0.039861023426056};
    std::vector<double> n12_ = {-1.463354110717773, 0.106234848499298, -0.062973946332932};
    std::vector<double> p20_ = {0.529286026954651, 0.369679987430573, 0.863919973373413};
    std::vector<double> n20_ = {0.811285793781281, 0.574435889720917, 0.108805976808071};
    std::vector<double> p21_ = {0.155601978302002, 0.167689025402069, -0.085048973560333};
    std::vector<double> n21_ = {-1.449134111404419, 0.165311336517334, 0.105492092669010};
    std::vector<double> p22_ = {0.061486959457397, 0.113540023565292, -0.136707961559296};
    std::vector<double> n22_ = {-1.402412891387939, 0.210225224494934, 0.077945031225681};

    // Test case for RR #2
    // double ans_alpha = 0.62987;
    // double ans_u = 0.00862558;
    // std::vector<double> pD_ = {1, 2, 1};
    // std::vector<double> pL_ = {0, 1, 0};
    // std::vector<double> p10_ = {0.511367, 0.472912, -0.172372};
    // std::vector<double> n10_ = {-0.709005, 0.658665, -0.251938};
    // std::vector<double> p11_ = {-0.168923, -0.132192, 0.172372};
    // std::vector<double> n11_ = {-0.0380941, -0.0756929, 0.571292};
    // std::vector<double> p12_ = {0.00229895, 0.087235, 0.172372};
    // std::vector<double> n12_ = {-0.00747013, -0.0468389, 0.587099};
    // std::vector<double> p20_ = {0.277168005704880, 0.386878013610840, -0.289471000432968};
    // std::vector<double> n20_ = {0.483563005924225, 0.717585027217865, 0.501236975193024};
    // std::vector<double> p21_ = {0.031031996011734, -0.018148005008698, 0.015516012907028};
    // std::vector<double> n21_ = {-0.608214974403381, -0.204608201980591, 0.348066747188568};
    // std::vector<double> p22_ = {0.065275996923447, 0.103565990924835, -0.052973002195358};
    // std::vector<double> n22_ = {-1.293977975845337, -0.135358095169067, -0.566347956657410};

    // // Test case for TT #1 (eta1/eta2=eta1/eta0=1.5041833)
    // double ans_alpha = 0.048989;
    // double ans_u = 0.405843;
    // std::vector<double> pD_ = {0, 3, 3};
    // std::vector<double> pL_ = {1, 0, -2};
    // std::vector<double> p10_ = {-0.47951, 0.188409, 0.394961};
    // std::vector<double> n10_ = {-0.558866, -0.062897, 0.826869};
    // std::vector<double> p11_ = {-0.011621, 0.134577, 0.035201};
    // std::vector<double> n11_ = {0.321876, -0.051988, 0.137826};
    // std::vector<double> p12_ = {-0.030836, 0.114573, 0.010995};
    // std::vector<double> n12_ = {-0.243505, -0.2679, -0.330106};
    // std::vector<double> p20_ = {-0.271035999059677, 0.079536996781826, -0.272576004266739};
    // std::vector<double> n20_ = {-0.126439988613129, -0.461173951625824, -0.878254890441895};
    // std::vector<double> p21_ = {-0.071738988161087, -0.049747996032238, 0.070618003606796};
    // std::vector<double> n21_ = {-0.031262993812561, -0.454199910163879, 0.507821917533875};
    // std::vector<double> p22_ = {-0.068792998790741, 0.043978005647659, 0.070188999176025};
    // std::vector<double> n22_ = {-0.606584846973419, 0.437246948480606, 0.198474049568176};

    //////////////////////////////////////////////////
    // Common definations

    double ans_v = 1 - ans_alpha - ans_u;

    // BVP(1, x) means BVP({{x}})
    BVP3 pD = {BVP(1, pD_[0]), BVP(1, pD_[1]), BVP(1, pD_[2])};
    BVP3 pL = {BVP(1, pL_[0]), BVP(1, pL_[1]), BVP(1, pL_[2])};

    BVP3 p10 = {BVP(1, p10_[0]), BVP(1, p10_[1]), BVP(1, p10_[2])};
    BVP3 p11 = {BVP(1, p11_[0]), BVP(1, p11_[1]), BVP(1, p11_[2])};
    BVP3 p12 = {BVP(1, p12_[0]), BVP(1, p12_[1]), BVP(1, p12_[2])};
    BVP3 n10 = {BVP(1, n10_[0]), BVP(1, n10_[1]), BVP(1, n10_[2])};
    BVP3 n11 = {BVP(1, n11_[0]), BVP(1, n11_[1]), BVP(1, n11_[2])};
    BVP3 n12 = {BVP(1, n12_[0]), BVP(1, n12_[1]), BVP(1, n12_[2])};

    BVP3 p20 = {BVP(1, p20_[0]), BVP(1, p20_[1]), BVP(1, p20_[2])};
    BVP3 p21 = {BVP(1, p21_[0]), BVP(1, p21_[1]), BVP(1, p21_[2])};
    BVP3 p22 = {BVP(1, p22_[0]), BVP(1, p22_[1]), BVP(1, p22_[2])};
    BVP3 n20 = {BVP(1, n20_[0]), BVP(1, n20_[1]), BVP(1, n20_[2])};
    BVP3 n21 = {BVP(1, n21_[0]), BVP(1, n21_[1]), BVP(1, n21_[2])};
    BVP3 n22 = {BVP(1, n22_[0]), BVP(1, n22_[1]), BVP(1, n22_[2])};

    BVP u1({{0, 0}, {1, 0}});
    BVP v1({{0, 1}, {0, 0}});

    BVP3 xD = pD;
    BVP3 xL = pL;
    BVP3 x1 = p10 + p11 * u1 + p12 * v1;
    BVP3 n1hat = n10 + n11 * u1 + n12 * v1;

    // The two polynomials we want to generate. Don't care the name.
    BVP Czy;
    BVP Cxz;

    BVP u2hat;
    BVP v2hat;
    BVP kappa2;

    //////////////////////////////////////////////////
    // Polynomial generation (please select one)

    ///////////////////////////////////
    // R: 5 degree form

    // BVP3 d0 = x1 - xD;
    // BVP3 d1 = xL - x1;
    // BVP d0_norm2 = d0.dot(d0);
    // BVP d1_norm2 = d1.dot(d1);
    // BVP3 c0 = d0.cross(n1hat);
    // BVP3 c1 = d1.cross(n1hat);
    // BVP3 c = c0 * c0 * d1_norm2 - c1 * c1 * d0_norm2;
    // Czy = c.bvp[0];
    // Cxz = c.bvp[1];

    ///////////////////////////////////
    // R: 2 + 4 degree form

    // BVP3 d0 = x1 - xD;
    // BVP3 d1 = xL - x1;
    // BVP d0_dot_n1hat = d0.dot(n1hat);
    // BVP d1_dot_n1hat = d1.dot(n1hat);
    // BVP3 t1hat1 = n1hat.cross(p11);
    // BVP3 t1hat2 = n1hat.cross(p12);
    // BVP d0_dot_t1hat2 = d0.dot(t1hat2);
    // BVP d1_dot_t1hat2 = d1.dot(t1hat2);
    // Czy = d0_dot_n1hat * d1_dot_t1hat2 + d0_dot_t1hat2 * d1_dot_n1hat;
    // BVP3 s = xL - xD;
    // BVP3 cop = (d0.cross(s)).cross(n1hat.cross(s));
    // Cxz = cop.bvp[0];

    ///////////////////////////////////
    // T: 6 degree form
    // double eta = 1.5041833;
    // BVP3 d0 = x1 - xD;
    // BVP3 d1 = xL - x1;
    // BVP d0_norm2 = d0.dot(d0);
    // BVP d1_norm2 = d1.dot(d1);
    // BVP3 c0 = d0.cross(n1hat);
    // BVP3 c1 = d1.cross(n1hat);
    // BVP3 c = c0 * c0 * d1_norm2 - c1 * c1 * d0_norm2 * BVP(1, eta * eta) ;
    // Czy = c.bvp[0];
    // Cxz = c.bvp[1];

    ///////////////////////////////////
    // RR: 15 degree form
    BVP3 d0 = x1 - xD;
    BVP3 omega1hat = d0 * (n1hat.dot(n1hat)) - n1hat * (n1hat.dot(d0)) * BVP(1, 2);
    u2hat = omega1hat.cross(p22).dot(x1 - p20);
    v2hat = (x1 - p20).cross(p21).dot(omega1hat);
    kappa2 = omega1hat.cross(p22).dot(p21);
    BVP3 x2hat = p20 * kappa2 + p21 * u2hat + p22 * v2hat;
    BVP3 d2hat = xL * kappa2 - x2hat;
    BVP3 n2hat = n20 * kappa2 + n21 * u2hat + n22 * v2hat;
    BVP3 t21hat = n2hat.cross(p21);
    BVP3 t22hat = n2hat.cross(p22);
    BVP omega1hat_dot_n2hat = omega1hat.dot(n2hat);
    BVP d2hat_dot_n2hat = d2hat.dot(n2hat);
    Czy = omega1hat_dot_n2hat * (d2hat.dot(t22hat)) + d2hat_dot_n2hat * (omega1hat.dot(t22hat));
    Czy.printCoefficientsMatrix();
    BVP cop = d2hat.cross(xL - x1).dot(n2hat);
    Cxz = cop;

    // ///////////////////////////////////
    // //TT:
    // double eta = 1.5041833;
    // BVP3 d0 = x1 - xD;
    // BVP3 p0 = p10, p1 = p10 + p11, p2 = p12 + p10;
    // BVP norm1 = (p0 - xD).dot(p0 - xD), norm2 = (p1 - xD).dot(p1 - xD), norm3 = (p2 - xD).dot(p2 - xD);
    // const double mu1 = std::max(std::max(norm1.coeffs[0][0], norm2.coeffs[0][0]), norm3.coeffs[0][0]);

    // BVP beta1 = n1hat.dot(n1hat) * d0.dot(d0) - (n1hat.dot(n1hat) * d0.dot(d0) - d0.dot(n1hat) * d0.dot(n1hat)) * BVP(1, 1 / (eta * eta));
    // beta1 = beta1 * BVP(1, 1 / mu1);
    // BVP3 first_term = (d0 * n1hat.dot(n1hat) - n1hat * d0.dot(n1hat)) * BVP(1, 1 / eta);
    // // 2 degree rational approximant :
    // const double a_0 = 5.88428458e-04, a_1 = 7.61441386e-01, a_2 = 3.40458305e+00,
    //              b_0 = 7.50718012e-02, b_1 = 2.55906806e+00, b_2 = 1.54868566e+00;
    // BVP numerator = BVP(1, a_0) + BVP(1, a_1) * beta1 + BVP(1, a_2) * beta1 * beta1;
    // BVP denominator = BVP(1, b_0) + BVP(1, b_1) * beta1 + BVP(1, b_2) * beta1 * beta1;
    // // 3 degree rational approximant :
    // // const double a_0 = 4.64579103e-05, a_1 = 2.78083875e+01, a_2 = 7.49056119e+02, a_3 = 1.16778434e+03,
    // //              b_0 = 1.32404066e+00, b_1 = 2.10703627e+02, b_2 = 1.34168102e+03, b_3 = 3.91642093e+02;
    // // BVP numerator = BVP(1, a_0) + BVP(1, a_1) * beta1 + BVP(1, a_2) * beta1 * beta1 + BVP(1, a_3) * beta1 * beta1 * beta1;
    // // BVP denominator = BVP(1, b_0) + BVP(1, b_1) * beta1 + BVP(1, b_2) * beta1 * beta1 + BVP(1, b_3) * beta1 * beta1 * beta1;
    // Please refer to the code for piecewise rational approximation

    // BVP3 omega1hat = first_term * denominator * BVP(1, 1 / std::sqrt(mu1)) - n1hat * numerator;
    // u2hat = omega1hat.cross(p22).dot(x1 - p20);
    // v2hat = (x1 - p20).cross(p21).dot(omega1hat);
    // kappa2 = omega1hat.cross(p22).dot(p21);
    // BVP3 x2hat = p20 * kappa2 + p21 * u2hat + p22 * v2hat;
    // BVP3 d1hat = x2hat - x1 * kappa2;
    // BVP3 d2hat = xL * kappa2 - x2hat;
    // BVP3 n2hat = n20 * kappa2 + n21 * u2hat + n22 * v2hat;
    // BVP d1_norm2 = d1hat.dot(d1hat);
    // BVP d2_norm2 = d2hat.dot(d2hat);
    // BVP3 c1 = d1hat.cross(n2hat);
    // BVP3 c2 = d2hat.cross(n2hat);
    // BVP3 c = c1 * c1 * d2_norm2 - c2 * c2 * d1_norm2 * BVP(1, eta * eta);
    // Czy = c.bvp[0];
    // // Cxz = c.bvp[1];
    // BVP3 s = xL - x1;
    // BVP3 cop = ((x2hat - x1 * kappa2).cross(s)).cross(n2hat.cross(s));
    // Cxz = cop.bvp[0];

    // Validate
    double val_Czy = Czy.evaluateAtV(ans_v).evaluateAtU(ans_u);
    double val_Cxz = Cxz.evaluateAtV(ans_v).evaluateAtU(ans_u);
    double val_u2hat = u2hat.evaluateAtV(ans_v).evaluateAtU(ans_u);
    double val_v2hat = v2hat.evaluateAtV(ans_v).evaluateAtU(ans_u);
    double val_kappa2 = kappa2.evaluateAtV(ans_v).evaluateAtU(ans_u);

    std::cout << "bvp Czy" << std::endl;
    Czy.printCoefficientsMatrix();
    std::cout << Czy.coeffs[0][0] << std::endl;
    std::cout << "bvp Cxz" << std::endl;
    Cxz.printCoefficientsMatrix();
    std::cout << Cxz.coeffs[0][0] << std::endl;

    std::cout << "bvp u2hat" << std::endl;
    u2hat.printCoefficientsMatrix();
    std::cout << "bvp v2hat" << std::endl;
    v2hat.printCoefficientsMatrix();
    std::cout << "bvp kappa2" << std::endl;
    kappa2.printCoefficientsMatrix();

    // std::cout << "Bezout" << std::endl;
    // auto bezout = bezout_matrix(Czy.toUnivariatePolynomials(), Cxz.toUnivariatePolynomials());
    // printUnivariatePolynomialMatrix(bezout);

    std::cout << "result Czy=" << val_Czy << "  Cxz=" << val_Cxz << std::endl;
    std::cout << "u v k " << val_u2hat << " " << val_v2hat << " " << val_kappa2 << std::endl;
}