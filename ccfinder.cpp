#ifdef _UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif
#include <iostream>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <vector>
#include <string>
#include "header.h"
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>


using namespace std;
using namespace boost::filesystem;
namespace fs = boost::filesystem;
namespace io = boost::iostreams;


bool checkLuhn(const string& cardNo)
{
        int nDigits = cardNo.length();

        int nSum = 0, isSecond = false;
        for (int i = nDigits - 1; i >= 0; i--) {

                int d = cardNo[i] - '0';

                if (isSecond == true)
                        d = d * 2;
                nSum += d / 10;
                nSum += d % 10;

                isSecond = !isSecond;
        }
        return (nSum % 10 == 0);
}

int main()
{
        cout << "CC Finder by independent 2.2 https://GitHub.com/independentcod All rights reserved" << std::endl;
        cout << "Please wait a few hours this will take a while..." << std::endl;
        cout << "---" << std::endl;
        std::ofstream fout("CCFinder.log", ios::app);
        fout << "CC Finder by independent 2.2 https://GitHub.com/independentcod All rights reserved" << std::endl;

                for (const auto& x : fs::recursive_directory_iterator("/home/")) {
                        if (x.path().extension() == ".txt" || x.path().extension() == ".dmp" || x.path().extension() == ".csv" || x.path().extension() == ".dat" || x.path().extension() == ".db" || x.path().extension() == ".dbf" || x.path().extension() == ".sql" || x.path().extension() == ".xml" || x.path().extension() == ".mdb" || x.path().extension() == ".sav" || x.path().extension() == ".html" || x.path().extension() == ".htm") {
                                if (boost::filesystem::is_regular_file(x.path())) {
                                        boost::filesystem::absolute(x.path().filename());
                                        fs::path entry = x;
                                        std::string line;
                                        std::cout << entry << std::endl;
                                        try
                                        {

                                                boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_source> bis(entry);
                                                std::istream myfile(&bis);
                                                boost::regex expr1("\\b\\d{15,16}\\b");
                                                boost::smatch what1;
                                                if (!myfile) {
                                                        cout << " Failed to open " << entry << endl;
                                                }
                                                while (getline(myfile, line))
                                                {
                                                        if (boost::regex_search(line, what1, expr1))
                                                        {

                                                                if (checkLuhn(what1.str())) {
                                                                        fout << line << std::endl;
                                                                        std::cout << line << std::endl;
                                                                        for (int i(0); i < what1.size(); i++) {
                                                                               std::cout << what1[i] << std::endl;
                                                                        }
                                                                }
                                                        }

                                                }
                                        }
                                        catch (const std::exception & ex)
                                        {

                                                std::cout << entry << " " << ex.what() << std::endl;
                                        }
                                }
                        }
                }
}