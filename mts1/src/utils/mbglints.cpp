/*
    This file is part of Mitsuba, a physically based rendering system.

    Copyright (c) 2007-2014 by Wenzel Jakob and others.

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

#include <mitsuba/render/util.h>
#include <mitsuba/core/timer.h>
#include <mitsuba/core/fresolver.h>
#include <mitsuba/core/plugin.h>
#include <boost/algorithm/string.hpp>
#if defined(WIN32)
#include <mitsuba/core/getopt.h>
#endif

#include <mutex>
std::mutex mu;
std::ofstream ofs("pathcut_log.txt");

#include "mbglints/glintbounce.h"
MTS_NAMESPACE_BEGIN


class MultiBounceGlint : public Utility {
public:
	void help() {
		cout << endl;
		cout << "Synopsis: Muliple Bounce Glint Computation" << endl;
		cout << endl;
		cout << "Usage: mtsutil mbglints [options] <Scene XML file or PLY file>" << endl;
		cout << "Options/Arguments:" << endl;
		cout << "   -h                 Display this help text" << endl << endl;
		cout << "   -b value           Specify the bounce count" << endl << endl;
		cout << "   -s value           Specify the spp" << endl << endl;
		cout << "   -e value           Specify the error threshold" << endl << endl;
		cout << "   -i value           Specify the iteration counts" << endl << endl;
        cout << "   -o name            Specify the output image name" << endl << endl;
        cout << "   -H name            Specify the heightfield image name (scale is forced as 0.5 now)" << endl << endl;
		cout << "	-P value 		   Specify the post-processing mode (Default is 0, meaning no post-process)" << endl << endl;
		cout << "   -l                 Use my_log" << endl << endl;
        cout << "   -L                 Use my_xlog" << endl << endl;
		cout << "   -r                 Use resultant" << endl << endl;
		cout << "   -R                 Use resultant fft" << endl << endl;
        cout << "   -n                 Use neural inference" << endl << endl;
		cout << "   -d				   Specify the max iterations for bisection" << endl << endl;
        cout << "   -D key=value       Other parameters specified for the scene file" << endl << endl;
	}

	int run(int argc, char **argv) {
		ref<FileResolver> fileResolver = Thread::getThread()->getFileResolver();

        std::string outputImage = "output.exr";
        float errorThresh = 0.001;
        int bounceCount = 1;
        int spp = 1;
        bool use_my_log = false;
        bool use_my_xlog = false;
        bool use_neural = false;
        bool use_resultant = false;
        bool use_resultant_fft = false;
		float scale_param = 0.5;
		int config_cutoff_matrix = 8;
		int config_cutoff_resultant = 100;
		float config_cutoff_eps_resultant = 1e-99;
		int itrCount = 32;
		int ouritrCount = 32;
		int methodMask = 0;
		int maxIterationDichotomy = 3; // max iteration for bisection
		int postProcessOption = EPostOption::NoProcess;
		std::string hfFilename = "";
        std::map<std::string, std::string, SimpleStringOrdering> parameters;
        Properties renderProps;

        int optchar;
        char *end_ptr = NULL;
		/* Parse command-line arguments */
		while ((optchar = getopt(argc, argv, "hlLnrRb:i:I:e:s:S:H:o:d:D:c:C:T:P:m:")) != -1) {
			SLog(EInfo, "optchar %c optarg %s", optchar, optarg);
			switch (optchar) {
				case 'h':
                    help();
                    return 0;
				case 'H':
                    hfFilename = optarg;
                    break;
				case 'b':
					bounceCount = strtol(optarg, &end_ptr,10);
					if (*end_ptr != '\0')
						SLog(EError, "Could not parse the bounce count!");
					break;
				case 's':
					spp = strtol(optarg, &end_ptr,10);
					if (*end_ptr != '\0')
						SLog(EError, "Could not parse the spp!");
					break;
				case 'S':
					scale_param = strtof(optarg, &end_ptr);
					if (*end_ptr != '\0')
						SLog(EError, "Could not parse the scale!");
					break;
                case 'e':
                    errorThresh = strtof(optarg, &end_ptr);
                    if (*end_ptr != '\0')
                        SLog(EError, "Could not parse the error threshold!");
                    break;
                case 'o':
                    outputImage = optarg;
                    if (!boost::ends_with(outputImage, ".exr")) {
                        SLog(EWarn, "Output image does not end wih .exr!");
                    }
                    break;
				case 'i':
					itrCount = strtol(optarg, &end_ptr,10);
					if(*end_ptr != '\0')
						SLog(EError, "Could not parse the iteration Count");
					break;
				case 'I':
					ouritrCount = strtol(optarg, &end_ptr,10);
					if(*end_ptr != '\0')
						SLog(EError, "Could not parse the our iteration Count");
					break;
				case 'm':
					methodMask = strtol(optarg, &end_ptr,10);
					if(*end_ptr != '\0')
						SLog(EError, "Could not parse the our methodMask");
					break;
				case 'l':
					SLog(EInfo, "use my_log");
					use_my_log = true;
					break;
				case 'L':
					SLog(EInfo, "use my_xlog");
					use_my_xlog = true;
					break;
                case 'n':
                    SLog(EInfo, "use neural inference");
                    use_neural = true;
                    break;
                case 'r':
                    SLog(EInfo, "use resultant solver");
                    use_resultant = true;
                    break;
                case 'R':
                    SLog(EInfo, "use resultant solver (FFT)");
                    use_resultant_fft = true;
                    break;
				case 'c':
					config_cutoff_matrix = strtol(optarg, &end_ptr,10);
					if (*end_ptr != '\0')
						SLog(EError, "Could not parse the cutoff (matrix)!");
					break;
				case 'C':
					config_cutoff_resultant = strtol(optarg, &end_ptr,10);
					if (*end_ptr != '\0')
						SLog(EError, "Could not parse the cutoff (resultant)!");
					break;
				case 'P':
					postProcessOption = strtol(optarg, &end_ptr, 10);
					if(*end_ptr != '\0')
						SLog(EError, "Could not parse the post process option!");
					break;
				case 'T':
					config_cutoff_eps_resultant = strtof(optarg, &end_ptr);
					if (*end_ptr != '\0')
						SLog(EError, "Could not parse the cutoff eps (resultant)!");
					break;
				case 'd':
					maxIterationDichotomy = strtol(optarg, &end_ptr, 10);
					if(*end_ptr != '\0')
						SLog(EError, "Could not parse the max iteration dichotomy!");
					break;
				case 'D':
					if (optarg == nullptr) {
						break;
					}
					std::vector<std::string> param = tokenize(optarg, "=");
					if (param.size() != 2)
						SLog(EError, "Invalid parameter specification \"%s\"", optarg);
					parameters[param[0]] = param[1];
                    break;
			};
		}

		ref<Scene> scene;
		ref<ShapeKDTree> kdtree;

		std::string xmlName = argv[argc - 1];
		if (boost::ends_with(xmlName, ".xml")) {
			fs::path
				filename = fileResolver->resolve(xmlName),
				filePath = fs::absolute(filename).parent_path(),
				baseName = filename.stem();
			ref<FileResolver> frClone = fileResolver->clone();
			frClone->prependPath(filePath);
			Thread::getThread()->setFileResolver(frClone);
			scene = loadScene(xmlName, parameters);
			kdtree = scene->getKDTree();
		} else {
			Log(EError, "Missing scene file (which should end with .xml)!");
		}

		/* Show some statistics, and make sure it roughly fits in 80cols */
		Logger *logger = Thread::getThread()->getLogger();
		DefaultFormatter *formatter = ((DefaultFormatter *) logger->getFormatter());
		logger->setLogLevel(EDebug);
		formatter->setHaveDate(false);

		scene->initialize();

//		string hfPath = "";
//		cout << argc << std::endl;
//		cout << outputImage << std::endl;
		BounceGlintRenderer *glintRender;
//		cout << "For heightfield input: mtsutil.exe mbglints xml output.exr heightfild.exr heightfieldScale bounceCount errorThresh(0.001)";
//		cout << "For mesh input: mtsutil.exe mbglints xml output.exr bounceCount errorThresh(0.001)";


		if (hfFilename != "") 
		{
			cout << "Using a height field. \n";
			float scale = scale_param; // todo: scale as param
			glintRender = new BounceGlintRenderer(scene, hfFilename, scale);
		}
		else
		{
			cout << "Using a general object. \n";
			glintRender = new BounceGlintRenderer(scene, use_neural);
		}

		glintRender->use_log = use_my_log;
		glintRender->use_xlog = use_my_xlog;
		glintRender->config_itrCount = itrCount;
		glintRender->config_ouritrCount = ouritrCount;
        glintRender->use_pruning = false;
        glintRender->use_resultant = use_resultant || use_resultant_fft;
        glintRender->use_resultant_fft = use_resultant_fft;
        glintRender->config_cutoff_matrix = config_cutoff_matrix;
        glintRender->config_cutoff_resultant = config_cutoff_resultant;
        glintRender->config_cutoff_eps_resultant = config_cutoff_eps_resultant;
        glintRender->methodMask = methodMask;
		glintRender->maxIterationDichotomy = maxIterationDichotomy;
		glintRender->setPostProcessOption(EPostOption(postProcessOption));
		clock_t t;
		t = clock();

		glintRender->renderOneImage(outputImage,bounceCount,spp, errorThresh); // "path.ply"

		t = clock() - t;
		if (global_log_flag) printf("It cost %f seconds).\n", ((float)t) / CLOCKS_PER_SEC);
		delete glintRender;
		return 0;
	}

	MTS_DECLARE_UTILITY()
};

MTS_EXPORT_UTILITY(MultiBounceGlint, "Multiple Bounce Glint Computation")
MTS_NAMESPACE_END
