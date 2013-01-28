
#include "Main.h"

const int mouseXTitle = 222;
const int mouseYTitle = 222;

const int mouseXClose = 688;
const int mouseYClose = 12;

struct SkpFileInfo
{
    SkpFileInfo() {}
    SkpFileInfo(const string &_id, const string &_filename, const string &_title, const string &_description, const string &_tags)
    {
        id = _id;
        filename = _filename;
        title = _title;
        description = _description;
        tags = _tags;
    }

    string id;
    string filename;
    string title;
    string description;
    string tags;
};

class App
{
public:
    void Go();

private:
    map<string,SkpFileInfo> _skpFiles;
};

void App::Go()
{
    ofstream log("Log.txt");

    string defaultTitle = "Model name unknown";
    string defaultTags = "Component";

    vector<string> modelList = Utility::GetFileLines("StanfordSceneDBModels.txt", 3);
    for(const string &id : modelList)
    {
        string description = "This is a model re-uploaded to 3D Warehouse for the Stanford Scene Database.\nIf still available, the original model can be found at: http://sketchup.google.com/3dwarehouse/details?mid=" + id + "\nSee http://graphics.stanford.edu/projects/scenesynth/ for more information.";
        _skpFiles[id] = SkpFileInfo(id, "C:\\SceneModeling\\Database\\SketchUp\\" + id + ".skp", defaultTitle + ". ID=" + id, description, defaultTags);
    }

    vector<string> modelNames = Utility::GetFileLines("names.txt", 3);
    vector<string> modelTags = Utility::GetFileLines("tags.txt", 3);

    for(const string &s : modelNames)
    {
        vector<string> parts = Utility::PartitionString(s, "|");
        string id = parts[0];
        if(_skpFiles.find(id) != _skpFiles.end())
        {
            if(parts[1] == "*") parts[1] = "Unnammed model";
            _skpFiles[id].title = parts[1] + ". ID=" + parts[0];
        }
    }

    for(const string &s : modelTags)
    {
        vector<string> parts = Utility::PartitionString(s, "|");
        string id = parts[0];
        if(_skpFiles.find(id) != _skpFiles.end())
        {
            string tags;
            for(UINT i = 1; i < parts.size(); i++)
            {
                tags += parts[i] + ",";
            }
            if(tags.length() > 0)
            {
                tags.pop_back();
                _skpFiles[id].tags = tags;
            }
        }
    }

    //PartitionString(const string &s, const string &separator)

    //_skpFiles.push_back(SkpFileInfo("C:\\SceneModeling\\Database\\SketchUp\\1a0c94a2e3e67e4a2e4877b52b3fca7.skp", "TITLE A!!!! AN OBJECT!!!", "DESCRIPTION!!! Here is some stuff that is sort of long and convoluted.", "TAGS!!!! APPLE ORANGE COUCH POTATO RUBIK'S CUBE"));
    //_skpFiles.push_back(SkpFileInfo("C:\\SceneModeling\\Database\\SketchUp\\1a1a7da3b8028d19cb98ab132d4b77f1.skp", "TITLE B!!!! AN OBJECT!!!", "DESCRIPTION!!! Here is some stuff that is sort of long and convoluted.", "TAGS!!!! APPLE ORANGE COUCH POTATO RUBIK'S CUBE"));
    //_skpFiles.push_back(SkpFileInfo("C:\\SceneModeling\\Database\\SketchUp\\1a1cfc219ddbae7f86e0b9bedd915f08.skp", "TITLE C!!!! AN OBJECT!!!", "DESCRIPTION!!! Here is some stuff that is sort of long and convoluted.", "TAGS!!!! APPLE ORANGE COUCH POTATO RUBIK'S CUBE"));
    //_skpFiles.push_back(SkpFileInfo("C:\\SceneModeling\\Database\\SketchUp\\1a1ec1cfe633adcdebbf11b1629fc16a.skp", "TITLE D!!!! AN OBJECT!!!", "DESCRIPTION!!! Here is some stuff that is sort of long and convoluted.", "TAGS!!!! APPLE ORANGE COUCH POTATO RUBIK'S CUBE"));

    BlockOnKey(KEY_NUMPADADD);

    for(const auto &pair : _skpFiles)
    {
        const auto &s = pair.second;
        if(Utility::FileExists("uploaded/" + s.id + ".dat"))
        {
            log  << "Skipping " << s.id << endl;
            cout << "Skipping " << s.id << endl;
        }
        else
        {
            ofstream uploadFile(("uploaded/" + s.id + ".dat").c_str());
            //
            // TODO: check if already exported (probably by creating a dummy file when we successfully upload?
            //
            log  << "Uploading " << s.id << endl;
            cout << "Uploading " << s.id << endl;

            //
            // Load the filename to load onto the clipboard
            //
            CopyStringToClipboard(s.filename);
            SendKey(KEY_O, true, false);
            SendKey(KEY_V, true, false);
            SendKey(KEY_ENTER, false, false);
            Sleep(1000);

            log  << "Clearing annoying save dialog" << endl;
            cout << "Clearing annoying save dialog" << endl;
            SendKey(KEY_ENTER, false, false);

            log  << "Waiting for file load to finish" << endl;
            cout << "Waiting for file load to finish" << endl;
            Sleep(5000);

            SendKey(KEY_F, false, true);
            SendKey(KEY_3, false, false);
            SendKey(KEY_ENTER, false, false);
            SendKey(KEY_S, false, false);

            log  << "Clearing remove unused objects window" << endl;
            cout << "Clearing remove unused objects window" << endl;
            Sleep(1000);
            SendKey(KEY_ENTER, false, false);

            log  << "Saving model" << endl;
            cout << "Saving model" << endl;
            Sleep(1000);

            SendKey(KEY_S, true, false);

            SendKey(KEY_ENTER, false, false);

            log  << "Waiting for upload page to load" << endl;
            cout << "Waiting for upload page to load" << endl;
            Sleep(1000);

            log  << "Clicking to set focus on title" << endl;
            cout << "Clicking to set focus on title" << endl;
            ClickMouse(mouseXTitle, mouseYTitle);
            Sleep(1000);

            log  << "Inputting fields" << endl;
            cout << "Inputting fields" << endl;

            CopyStringToClipboard(s.title);
            SendKey(KEY_V, true, false);
            SendKey(KEY_TAB, false, false);

            CopyStringToClipboard(s.description);
            SendKey(KEY_V, true, false);
            SendKey(KEY_TAB, false, false);

            CopyStringToClipboard(s.tags);
            SendKey(KEY_V, true, false);
            SendKey(KEY_TAB, false, false);
            SendKey(KEY_TAB, false, false);

            Sleep(500);
            SendKey(KEY_ENTER, false, false);

            log  << "Waiting for upload to finish" << endl;
            cout << "Waiting for upload to finish" << endl;
            Sleep(30000);

            log  << "Exiting browser" << endl;
            cout << "Exiting browser" << endl;
            ClickMouse(mouseXClose, mouseYClose);
            Sleep(1000);

            if(GetAsyncKeyState(VK_ESCAPE))
            {
                BlockOnKey(KEY_NUMPADADD);
            }
        }
    }
}

void main()
{
    App a;
    a.Go();
}