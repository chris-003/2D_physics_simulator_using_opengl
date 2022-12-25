#include "exception.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/file_status.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <tuple>

void for_each(
    const std::function<void(const std::string                     &dir,
                             const std::tuple<std::string, size_t> &i)> &func,
    boost::property_tree::basic_ptree<std::string,
                                      std::tuple<std::string, size_t>>
                pt,
    std::string prefix = "") {
    if (pt.size() == 0) {
        auto data = pt.get_value<std::tuple<std::string, size_t>>();
        func(prefix, data);
        // std::cout << prefix << " -> " << std::get<0>(data) << ": "
        //           << std::get<1>(data) << "bytes." << std::endl;
        return;
    }
    // else
    for (auto iter = pt.begin(); iter != pt.end(); ++iter) {
        for_each(func, iter->second, prefix + "/" + iter->first);
    }
}

// func(std::string full_path, std::stirng relative_path)
void foreachFileInDir(
    const boost::filesystem::path                                &dir,
    std::function<void(const std::string &, const std::string &)> func) {
    std::queue<std::pair<boost::filesystem::path, boost::filesystem::path>>
        q; // first for full path and second for prefix(relative path)
    boost::filesystem::directory_iterator i(dir);
    boost::filesystem::path               currentPrefix(".");
    do {
        if (i == boost::filesystem::end(i)) {
            if (q.empty()) {
                return;
            }
            // else
            auto _dir = q.front();
            q.pop();
            i             = boost::filesystem::directory_iterator(_dir.first);
            currentPrefix = _dir.second;
        }
        // else
        if (boost::filesystem::is_regular(i->path())) {
            func(i->path().string(),
                 (currentPrefix / i->path().filename()).string());
        }
        else if (boost::filesystem::is_directory(i->path())) {
            q.push(std::make_pair<const boost::filesystem::path &,
                                  const boost::filesystem::path &>(
                i->path(), currentPrefix / i->path().filename()));
        }
        ++i;
    } while (!q.empty() || (i != boost::filesystem::end(i)));
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        return 1;
    }
    std::string srcPath, destPath;
    if (std::string(argv[1]) == std::string("-o")) {
        srcPath  = std::string(argv[3]);
        destPath = std::string(argv[2]);
    }
    else if (std::string(argv[2]) == std::string("-o")) {
        srcPath  = std::string(argv[1]);
        destPath = std::string(argv[3]);
    }
    else {
        return 2;
    }

    if (!boost::filesystem::exists(boost::filesystem::path(srcPath))) {
        throw FileNotExistError("File Not Exist: " + srcPath);
    }

    boost::filesystem::path filenamePrefix =
        boost::filesystem::system_complete(boost::filesystem::path(srcPath))
            .branch_path();
    std::string srcFilename =
        boost::filesystem::path(srcPath).filename().string();
    {
        std::ofstream out(destPath, std::ios::ate | std::ios::out);
        out.close();
    }
    std::string destFullPath =
        boost::filesystem::system_complete(boost::filesystem::path(destPath))
            .string();

    boost::filesystem::current_path(filenamePrefix);
    // if (boost::filesystem::path(srcPath).is_complete()) {
    //     filenamePrefix = boost::filesystem::path(srcPath).branch_path();
    // }
    // else {
    //     filenamePrefix = (boost::filesystem::current_path() / ;
    // }
    std::cout << "Compiling resource file " << srcPath << " to " << destPath
              << std::endl;
    std::cout << "  branch name: " << filenamePrefix << std::endl;

    std::ifstream     in(srcFilename);
    std::stringstream outBuffer;
    std::ofstream     out(destFullPath, std::ios::ate | std::ios::out);
    boost::property_tree::ptree in_ptree;
    boost::property_tree::basic_ptree<std::string,
                                      std::tuple<std::string, size_t>>
        out_ptree; // std::tuple<string, string, size_t>: filename, size
    boost::property_tree::xml_parser::read_xml(
        in, in_ptree,
        boost::property_tree::xml_parser::no_comments |
            boost::property_tree::xml_parser::trim_whitespace);

    for (auto i = in_ptree.begin(); i != in_ptree.end(); ++i) {
        if (i->first == std::string("resource")) {
            std::string id =
                i->second.get<std::string>("<xmlattr>.id", "Resource");
            for (auto j = i->second.begin(); j != i->second.end(); ++j) {
                if (j->first == std::string("prefix")) {
                    std::string prefix =
                        j->second.get<std::string>("<xmlattr>.dir", ".");
                    for (auto k = j->second.begin(); k != j->second.end();
                         ++k) {
                        if (k->first == std::string("file")) {
                            // try to add a file
                            std::string filename, filenameAlias;
                            filename      = k->second.get_value<std::string>();
                            filenameAlias = k->second.get<std::string>(
                                "<xmlattr>.alias",
                                boost::filesystem::path(filename)
                                    .filename()
                                    .string());
                            filename = filenamePrefix.string() + "/" + filename;
                            if (!boost::filesystem::exists(filename)) {
                                throw FileNotExistError(
                                    std::string("File doesn't exists: ") +
                                    (boost::filesystem::path(prefix) /
                                     boost::filesystem::path(filename))
                                        .lexically_normal()
                                        .string());
                            }
                            auto status = boost::filesystem::status(filename);
                            switch (status.type()) {
                            case boost::filesystem::file_type::regular_file: {
                                size_t fileSize =
                                    boost::filesystem::file_size(filename);
                                std::string dir =
                                    boost::filesystem::path(prefix + "/" +
                                                            filenameAlias)
                                        .lexically_normal()
                                        .string();
                                out_ptree.put(
                                    boost::property_tree::path(dir, '/'),
                                    std::tuple<std::string, size_t>(filename,
                                                                    fileSize));
                                break;
                            }
                            defualt : {
                                throw FileTypeError(
                                    std::string("File type ERROR: ") +
                                    boost::filesystem::path(filename)
                                        .lexically_normal()
                                        .string() +
                                    std::string(
                                        "\nFile should be a regular file."));
                                break;
                            }
                            }
                        }
                        else if (k->first == std::string("directory")) {
                            std::string dir =
                                k->second.get_value<std::string>(std::string());
                            std::string __dir = dir;
                            {
                                auto _dir = boost::filesystem::path(dir)
                                                .lexically_normal();
                                if (_dir.filename_is_dot()) {
                                    dir = _dir.branch_path().string();
                                }
                                else if (_dir.filename_is_dot_dot()) {
                                    dir =
                                        boost::filesystem::system_complete(_dir)
                                            .string();
                                }
                            }
                            if (dir == std::string()) {
                                throw DirectoryNotExistError(
                                    "Directory Not Exist: " + dir);
                            }
                            std::string dirAlias = k->second.get<std::string>(
                                boost::property_tree::path("<xmlattr>.alias",
                                                           '/'),
                                boost::filesystem::path(dir)
                                    .filename()
                                    .string());
                            if (!boost::filesystem::exists(dir)) {
                                throw DirectoryNotExistError(
                                    "Directory Not Exist: " + __dir);
                            }
                            if (!boost::filesystem::is_directory(dir)) {
                                throw DirectoryNotExistError(
                                    "Directory Not Exist: " + __dir);
                            }
                            boost::filesystem::directory_iterator end_iter;
                            foreachFileInDir(
                                dir,
                                [&prefix, &out_ptree](
                                    const std::string &full,
                                    const std::string &relative) -> void {
                                    std::string filename =
                                        boost::filesystem::path(full)
                                            .filename()
                                            .string();
                                    size_t fileSize =
                                        boost::filesystem::file_size(full);
                                    std::string directory =
                                        boost::filesystem::path(prefix + "/" +
                                                                relative)
                                            .lexically_normal()
                                            .string();
                                    out_ptree.put(
                                        boost::property_tree::path(directory,
                                                                   '/'),
                                        std::tuple<std::string, size_t>(
                                            full, fileSize));
                                });
                            // for (boost::filesystem::directory_iterator
                            // i(dir);
                            //      i != end_iter; ++i) {
                            //     if (boost::filesystem::is_regular(
                            //             i->status())) {
                            //         // i->path().lexically_relative(dir);
                            //         std::string filename =
                            //         i->path().string(); size_t      fileSize
                            //         =
                            //             boost::filesystem::file_size(filename);
                            //         std::string directory =
                            //             boost::filesystem::path(prefix + "/"
                            //             +
                            //                                     filename)
                            //                 .lexically_normal()
                            //                 .string();
                            //         out_ptree.put(
                            //             boost::property_tree::path(directory,
                            //                                        '/'),
                            //             std::tuple<std::string, size_t>(
                            //                 filename, fileSize));
                            //     }
                            // }
                        }
                    }
                }
            }
            out << "#include <boost/property_tree/ptree.hpp>\n\n";
            out << "namespace SResourceData {\n";
            // out << "    extern boost::property_tree::basic_ptree<std::string,
            // "
            //        "std::pair<const char *, int>> resource_pt;\n";
            out << R"(boost::property_tree::basic_ptree<std::string, std::pair<const char *, int>> &getResourcePTree();)"
                << "\n";
            out << "    namespace " << id << " {\n";
            out << "        const char data[] = {";
            const int N   = 16;
            int       cnt = N;
            for_each(
                [&out,
                 &cnt](const std::string                     &dir,
                       const std::tuple<std::string, size_t> &data) -> void {
                    // static int    cnt = 8;
                    std::ifstream f(std::get<0>(data));
                    char          c;
                    for (int i = 0; i < std::get<1>(data); ++i) {
                        if (cnt == N) {
                            out << "\n           "; // 2 tabs and 3 spaces
                            cnt = 0;
                        }
                        f.read(&c, 1);
                        out << " 0x" << std::setw(2) << std::setfill('0')
                            << std::hex << (int)c << ',';
                        out << std::setw(0) << std::setfill(' ') << std::dec;
                        ++cnt;
                    }
                    if (cnt == N) {
                        out << "\n           "; // 2 tabs and 3 spaces
                        cnt = 0;
                    }
                    // f.read(&c, 1);
                    out << " 0x00,";
                    out << std::setw(0) << std::setfill(' ') << std::dec;
                    ++cnt;
                    f.close();
                },
                out_ptree);
            if (cnt == N) {
                out << "\n           "; // 2 tabs and 3 spaces
                cnt = 0;
            }
            out << " 0x00\n";
            out << "        };\n";
            // out << "        boost::property_tree::basic_ptree<std::string, "
            //        "std::pair<const char *, int>> pt;\n";
            out << "        class Dummy {\n";
            out << "        public:\n";
            out << "            Dummy() {\n";
            out << "                auto &resource_pt = "
                   "getResourcePTree();\n";
            for_each(
                [&out,
                 &id](const std::string                     &dir,
                      const std::tuple<std::string, size_t> &data) -> void {
                    static int fileSizeTotal = 0;
                    out << "                "; // 4 tabs
                    out << "resource_pt.put(boost::property_tree::path("
                           "\""
                        << id << "/:" << dir
                        << "\", \'/\'), std::make_pair<const char *, "
                           "int>(&data["
                        << fileSizeTotal << "], " << std::get<1>(data)
                        << "));\n";
                    fileSizeTotal += std::get<1>(data) + 1;
                },
                out_ptree);
            // out << "                "
            //        "resource_pt.add(boost::property_tree::path(\"";
            // out << id;
            // out << "\", '/'), pt);\n";
            out << "            }\n";
            out << "        } dummy;\n";
            out << "    }\n";
            out << "}\n";
        }
    }
    return 0;
}