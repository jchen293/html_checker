/**
 * Author: Junjie Chen
 * 11/14/2017
 */


#include "Tag.hpp"
#include <string>
#include <algorithm>
#include <sstream>
#include <stack>

using namespace std;


bool htmlIsValid(const std::string &document) {
    stack<string> stack;
    string tempHead, tempBody, tempHtml;
    string data = document;
    if (data.find("</head") != string::npos) {
        tempHead = "<head>";
    } else {
        return false;
    }
    if (data.find("</body") != string::npos) {
        tempBody = "<body>";
    } else {
        return false;
    }
    if (data.find("</html") != string::npos) {
        tempHtml = "<html>";
    } else {
        return false;
    }
    if (data.find("<html") != string::npos) {
        stack.push("<html>");
        if (((data.find("<head") != string::npos && data.find("<body") != string::npos)) &&
            ((data.find("<html") < data.find("<head")) && ((data.find("<html") < data.find("<body"))) &&
             (data.find("<head") < data.find("<body")))) {
            stack.push("<head>");
            if ((!stack.empty()) && (stack.top() == tempHead) &&
                (data.find("</head") && (data.find("</head") < data.find("</body")) &&
                 (data.find("</head") < data.find("<body")))) {
                stack.pop();
            } else {
                return false;
            }
            stack.push("<body>");
            if ((!stack.empty()) && (stack.top() == tempBody) && (data.find("</head") < data.find("</body"))) {
                stack.pop();
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
    if (!stack.empty() && stack.top() == tempHtml) {
        stack.pop();
    } else {
        return false;
    }
    if (stack.empty()) {
        return true;
    } else {
        return false;
    }
}

bool headIsValid(const std::string &document) {
    stack<string> stack;
    string data = document;
    string tempHead, tempTitle;

    if (data.find("</head") != string::npos) {
        tempHead = "<head>";
    } else {
        return false;
    }
    if (data.find("</title") != string::npos) {
        tempTitle = "<title>";
    } else {
        return false;
    }
    if (data.find("<head") != string::npos) {
        stack.push("<head>");
        if (data.find("<title") != string::npos && (data.find("<head") < data.find("<title"))) {
            stack.push("<title>");
            if ((!stack.empty()) && (stack.top() == tempTitle) && (data.find("</title>") < data.find("</head>"))) {
                stack.pop();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    if (!stack.empty() && stack.top() == tempHead) {
        stack.pop();
    } else {
        return false;
    }

    return true;
}

bool bodyIsValid(const std::string &document) {
    string data = document;
    string tempBody;
    for (int i = 0; i < document.length(); i++) {
        data[i] = tolower(document[i]);
    }

    string temp = data.substr(data.find("<body"), data.find("</body") - data.find("<body"));
    if (string::npos != temp.find("id") && temp.find("id") < data.find(">"))
    {
        bool flag = false;
        int i = temp.find("id");
        while (true) {
            if (temp.at(i) == '\"') {
                if (!flag)
                    flag = true;
                else
                    break;
            }
            if (flag && temp.at(i) == ' ')
                return false;
            i++;
        }
    }
    data.erase(remove(data.begin(), data.end(), ' '), data.end());

    if (data.find("</body") != string::npos) {
        tempBody = "<body>";
    } else {
        return false;
    }

    std::string contentBefore = data.substr(data.find("<html"), data.find("<body") - data.find("<html"));
    std::string contentAfter = data.substr(data.find("</body>") + 7, data.find("</html") - data.find("</body>"));
    if (data.find("<body") != string::npos) {
        if (contentAfter.find("<div") != string::npos || contentAfter.find("<p") != string::npos ||
            contentAfter.find("<br") != string::npos || contentAfter.find("<span") != string::npos) {
            return false;
        } else if (contentBefore.find("<div") != string::npos || contentBefore.find("<p") != string::npos ||
                   contentBefore.find("<br") != string::npos || contentBefore.find("<span") != string::npos) {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

bool titileIsValid(const std::string &document) {
    string data = document;
    string tempTitle;

    if (data.find("</title") != string::npos) {
        tempTitle = "<title>";
    } else {
        return false;
    }
    if (data.find("<title") != string::npos && (data.find("<title") < data.find("</title"))) {
    } else {
        return false;
    }
    if ((data.find("<p>") < data.find("</title>"))) {
        return false;
    }

    if (data.find("<title") != string::npos) {
        std::string content = data.substr(data.find("<title>") + 7,
                                          data.find("</title>") - (data.find("<title>") + 7));
        if (content.empty()) {
            return false;
        }
    } else {
        return false;
    }

    return true;
}

bool divIsValid(const std::string &document) {
    string data = document;
    return true;
}

bool pIsValid(const std::string &document) {
    string data = document;

    if (data.find("<p") != string::npos) {
        if (data.find("</p>") == string::npos || data.find("<p") > data.find("</p>")) {
            return false;
        }
    }
    return true;
}

bool brIsValid(const std::string &document) {
    string data = document;

    if (data.find("</br>") != string::npos) {
        return false;
    }
    if (data.find("<br/>") != string::npos) {
        return true;
    } else if (data.find("/>") != string::npos) {
        return false;
    }
    return true;
}

bool spanIsValid(const std::string &document) {
    string data = document;

    int i = 0, j = 0, t = -1;

    int s = data.find("<span");

    int temp[10], temp2[10];
    do {
        t = data.find("<span", t + 1);
        if (t == string::npos)
            break;
        temp[i++] = t;
    } while (1);
    do {
        t = data.find("</span>", t + 1);
        if (t == string::npos)
            break;
        temp2[j++] = t;
    } while (1);
    string content;
    if (i != j)
        return false;
    while (i--) {
        content = data.substr(temp[i], temp2[i] - temp[i] + 7);
        if (content.find("<head") != string::npos || content.find("<html") != string::npos ||
            content.find("<body") != string::npos ||
            content.find("<br") != string::npos ||
            content.find("<title") != string::npos ||
            content.find("<div") != string::npos || content.find("<p") != string::npos) {
            return false;
        }
    }

    string spanTemp = data.substr(data.find("<span") + 5, data.find("</span") - data.find("<span") + 5);
    if (spanTemp.find("<span") != string::npos || spanTemp.find("<html") != string::npos ||
        spanTemp.find("<body") != string::npos || spanTemp.find("<br") != string::npos ||
        spanTemp.find("<title") != string::npos || spanTemp.find("<p") != string::npos ||
        spanTemp.find("<div") != string::npos) {
        return false;
    }
    return true;
}

bool checkExtra(const std::string &document) {
    string data = document;
    if (data.find("<p/>") != string::npos || data.find("<span/>") != string::npos ||
        data.find("<head/>") != string::npos || data.find("<div/>") != string::npos ||
        data.find("<body/>") != string::npos || data.find("<title/>") != string::npos ||
        data.find("<html/>") != string::npos) {
        return false;
    }
    return true;
}

int NumOfTag(const string &document, const string str) {
    int num = 0;
    int pos = -1;
    do {
        pos = document.find(str, pos + 1);
        if (pos != -1)
            num++;
        else
            break;
    } while (true);
    return num;
}

bool html_is_valid(const std::string &document) {
    string data = document;
    for (int i = 0; i < document.length(); i++) {
        data[i] = tolower(document[i]);
    }
    data.erase(remove(data.begin(), data.end(), ' '), data.end());

        if (data.find("<!doctypehtml") == string::npos) {
        return false;
    }
    if (data.find("/ >") != string::npos) {
        return false;
    }
    if ((data.find("</head>", data.find("</head>") + 1)) != string::npos) {
        return false;
    }
    if ((data.find("<head", data.find("<head") + 1)) != string::npos) {
        return false;
    }
    if ((data.find("</html>", data.find("</html>") + 1)) != string::npos) {
        return false;
    }
    if ((data.find("<html", data.find("<html") + 1)) != string::npos) {
        return false;
    }
    if ((data.find("</body>", data.find("</body>") + 1)) != string::npos) {
        return false;
    }
    if ((data.find("<body", data.find("<body") + 1)) != string::npos) {
        return false;
    }
    if ((data.find("<title", data.find("<title") + 1)) != string::npos) {
        return false;
    }
    if ((data.find("</title>", data.find("</title>") + 1)) != string::npos) {
        return false;
    }
    if ((data.find("<!doctype html>", data.find("<!doctype html>") + 1)) != string::npos) {
        return false;
    }
    if (data.find("</html><") != string::npos) {
        return false;
    }

    if (NumOfTag(data, "<html") != NumOfTag(data, "</html")) {
        return false;
    }
    if (NumOfTag(data, "<head") != NumOfTag(data, "</head")) {
        return false;
    }
    if (NumOfTag(data, "<body") != NumOfTag(data, "</body")) {
        return false;
    }
    if (NumOfTag(data, "<title") != NumOfTag(data, "</title")) {
        return false;
    }
    if (NumOfTag(data, "<div") != NumOfTag(data, "</div")) {
        return false;
    }
    if (NumOfTag(data, "<p") != NumOfTag(data, "</p")) {
        return false;
    }
    if (NumOfTag(data, "<span") != NumOfTag(data, "</span")) {
        return false;
    }

    bool html = htmlIsValid(data);
    bool head = headIsValid(data);
    bool body = bodyIsValid(document);
    bool title = titileIsValid(data);
    bool div = divIsValid(data);
    bool p = pIsValid(data);
    bool br = brIsValid(data);
    bool span = spanIsValid(data);
    bool checkextra = checkExtra(data);

    return html && head && body && title && div && p && br && span && checkextra;
}
