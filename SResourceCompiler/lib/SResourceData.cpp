#include "include/SResourceData.h"

namespace SResourceData {

boost::property_tree::basic_ptree<std::string, std::pair<const char *, int>> &
getResourcePTree() {
    static boost::property_tree::basic_ptree<std::string,
                                             std::pair<const char *, int>>
        resource_pt;

    return resource_pt;
}

boost::property_tree::basic_ptree<std::string, std::pair<const char *, int>>
get_resource(const std::string &id) {
    return getResourcePTree().get_child(boost::property_tree::path(id, '/'));
}

std::pair<const char *, int>
get(const boost::property_tree::basic_ptree<
        std::string, std::pair<const char *, int>> &resource,
    const std::string                              &path) {
    return resource.get(boost::property_tree::path(path, '/'),
                        std::make_pair<const char *, int>(nullptr, 0));
}

// std::pair<const char *, int>
// get(const boost::property_tree::basic_ptree<
//         std::string, std::pair<const char *, int>> &resource,
//     const boost::property_tree::path               &path) {
//     return resource.get(path, std::make_pair<const char *, int>(nullptr, 0));
// }
} // namespace SResourceData