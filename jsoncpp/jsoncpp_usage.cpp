#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <boost/format.hpp>
#include <json/json.h>

using namespace std;

/*
 * jsoncpp 不存在的元素用默认构造函数
 * jv["non_exist"].asString() == ""
 * jv["non_exist"].asInt() == 0
 * 用下标访问数组
 *     for (Json::ArrayIndex i = 0; i < jsTaskArr.size(); ++i)
        Json::Value &item = jsTaskArr[i];
 */

void iterate_json(const Json::Value &root)
{
    // cout << "Json test" << endl;
    // cout << root.size() << endl;
    for (auto it = root.begin(); it != root.end(); ++it) {
        if (it->isObject())
            cout << it.key() << " is object" << endl;
        else
            cout << it.key() << " is not object" << endl;
        cout << boost::format("%s = %s") % it.key().asString() % it->asString() << endl;
        // cout << it.key() << endl;
    } // for
    // for (const auto &key : root.getMemberNames()) {
        // cout << key << endl;
    // } // for key

    // for (const auto &key : root.getMemberNames())
        // cout << boost::format("%s = %s") % key % root.get(key, Json::Value()) << endl;
}

#if 0
static
void test(const std::string &inFile)
{
    ifstream ifs(inFile, ios::in);
    ostringstream oss;

    oss << ifs.rdbuf() << flush;

    Json::Reader    reader;
    Json::Value     root;
    string          encoding;

    if (!reader.parse(oss.str(), root)) {
        cerr << "Invalid json!" << endl;
        return;
    } // if

    Json::Value &jv = root["encoding"];
    if (!jv) {
        cerr << "No attr \"encoding\" found!" << endl;
    } else {
        encoding = jv.asString();
        cout << encoding << endl;
        try {
            int n = jv.asInt();
            cout << n << endl;
        } catch (const Json::LogicError &err) {
            cerr << err.what() << endl;
        } // try
    } // if
}
#endif


void test_iterate_json()
{
    std::string str = "{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";
    // std::string str = "[\"how\", \"are\", \"you\"]";
    Json::Reader reader;
    Json::Value root;

    if (reader.parse(str, root))
        iterate_json(root);
    else
        cerr << "invalid json" << endl;
}


int main(int argc, char **argv)
try {
    // test(argv[1]);
    test_iterate_json();

    return 0;

} catch (const std::exception &ex) {
    std::cerr << "Exception caught by main: " << ex.what() << std::endl;
    return -1;
}


// #if 0
// example
void gen_json(const std::string &filename, const std::vector<FeatureInfo::pointer> &fields)
{
    using namespace std;

    Json::Value root;
    root["nfeatures"] = (Json::UInt)(fields.size());
    root["sep"] = "," SPACES;

    for (const auto &pf : fields) {
        Json::Value fItem;
        fItem["name"] = pf->name;
        fItem["type"] = pf->type;
        for (const string &v : pf->values)
            fItem["values"].append(v);
        // 这样插入新数组元素 insert new array elem
        auto &back = root["features"].append(Json::Value());
        back.swap(fItem);
    } // for

    Json::StyledWriter writer; // human readable
    string outStr = writer.write(root);

    ofstream ofs(filename, ios::out);
    THROW_RUNTIME_ERROR_IF(!ofs, "Cannot open " << filename << " for writting!");
    ofs << outStr << flush;
}
// #endif



#if 0
// Configuration options
{
    // Default encoding for text
    "encoding" : "UTF-8",

    // Plug-ins loaded at start-up
    "plug-ins" : [
        "python",
        "c++",
        "ruby"
        ],

    // Tab indent size
    "indent" : { "length" : 3, "use_space": true }
}
#endif

