#include <curl/curl.h>
#include <libxml/HTMLparser.h>
#include <libxml/parser.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#define CLEAR "clear"
#ifdef _WIN32
#undef CLEAR
#define CLEAR "cls"
#endif

using namespace std;

vector<string> nations;
vector<double> rates;

std::string trim(const std::string &str) {
    if(str.length() == 0)    {
        return str;
    }

    int first = str.find_first_not_of("\n\t ");
    int last = str.find_last_not_of("\n\t ");

    return std::string(str, first, last - first + 1);
}

int writer(char *data, int size, int nmemb, string *writerData)    {
	if (writerData == NULL)
		return 0;

	writerData->append(data, size*nmemb);
	return size * nmemb;
}

void parseItem(xmlDocPtr doc, xmlNodePtr cur){ 
    xmlChar *key; 
    cur = cur->xmlChildrenNode; 
    while (cur != NULL) { 
        if((!xmlStrcmp(cur->name, (const xmlChar *) "td"))) {
            if((!xmlStrcmp(xmlNodeGetContent((const xmlNode *)cur->properties), (const xmlChar *)"tit")))   {
                key = xmlNodeGetContent((const xmlNode *)cur->xmlChildrenNode);
                string str((char *)key);
                str = trim(str);
                nations.push_back(str);
                xmlFree(key); 
            }
            else if((!xmlStrcmp(xmlNodeGetContent((const xmlNode *)cur->properties), (const xmlChar *)"sale"))) { 
                key = xmlNodeGetContent((const xmlNode *)cur->xmlChildrenNode);
                string str((char *)key);
                str.erase(remove(str.begin(), str.end(), ','), str.end());
                rates.push_back(atof(str.c_str()));
                xmlFree(key); 
            }
        }
        cur = cur->next;
    } 
    return; 
}

static void parseDoc(const string &docname) { 
    xmlDocPtr doc; 
    xmlNodePtr cur; 
    doc = htmlReadMemory(docname.c_str(), docname.length(), "noname.xml", "EUC-KR", 0); 
    if (doc == NULL) { 
        fprintf(stderr,"Document not parsed successfully. \n"); 
        return; 
    } 
    
    cur = xmlDocGetRootElement(doc); 
    if (cur == NULL) { 
        fprintf(stderr,"empty document\n"); 
        xmlFreeDoc(doc); 
        return; 
    } 

    cur = cur->xmlChildrenNode;

    while (cur != NULL) { 
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"body"))){ 
            cur = cur->xmlChildrenNode; 
            while (cur != NULL) { 
                if((!xmlStrcmp(cur->name, (const xmlChar *)"div"))) { 
                    cur = cur->xmlChildrenNode; 
                    while (cur != NULL) { 
                        if((!xmlStrcmp(cur->name, (const xmlChar *)"table"))) { 
                            cur = cur->xmlChildrenNode; 
                            while (cur != NULL) { 
                                if((!xmlStrcmp(cur->name, (const xmlChar *)"tbody"))) { 
                                    cur = cur->xmlChildrenNode; 
                                    while (cur != NULL) { 
                                        if((!xmlStrcmp(cur->name, (const xmlChar *)"tr"))) { 
                                            parseItem(doc, cur); 
                                        } 
                                        cur = cur->next; 
                                    }
                                    return ;  
                                } 
                                cur = cur->next; 
                            }
                        } 
                        cur = cur->next; 
                    }
                } 
                cur = cur->next; 
            } 
        } 
        cur = cur->next;
    } 
}

double exchangeWon()    {
    int choose;
    int money;
    double rate;
    for(int i = 0; i < nations.size(); ++i)   {
        cout << i + 1 << " : " << nations[i] << "\n";
    }
    cout << "환전을 원하시는 화폐단위를 입력해주세요" << "\n";
    cin >> choose;
    if(choose < 0 || choose > nations.size())   {
        cout << "Error" << "\n";
        return -1;
    }
    rate = rates[choose - 1];
    if(nations[choose - 1].find("100") != string::npos)  {
        rate /= 100;
    }
    cout << "한국 KOR : " << nations[choose - 1] + " = " << rates[choose - 1] << " : 1" << "\n";
    cout << "얼마를 환전하실건가요?" << "\n";
    cin >> money;

    return money / rate;
}

double exchangeOther()  {
    int choose;
    int money;
    double rate;
    for(int i = 0; i < nations.size(); ++i)   {
        cout << i + 1 << " : " << nations[i] << "\n";
    }
    cout << "환전을 원하시는 화폐단위를 입력해주세요" << "\n";
    cin >> choose;
    if(choose < 0 || choose > nations.size())   {
        cout << "Error" << "\n";
        return -1;
    }
    rate = rates[choose - 1];
    if(nations[choose - 1].find("100") != string::npos)  {
        rate /= 100;
    }
    cout << "한국 KOR : " << nations[choose - 1] + " = " << rates[choose - 1] << " : 1" << "\n";
    cout << "얼마를 환전하실건가요?" << "\n";
    cin >> money;

    return money * rate;
}

int main(void)  {
	CURL *curl;
	CURLcode res;
    int choose;

	curl = curl_easy_init();
	
	if(curl) {
		string html;	
		curl_easy_setopt(curl, CURLOPT_URL, "http://info.finance.naver.com/marketindex/exchangeList.nhn");
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);

        parseDoc(html);
	}

    while(1)    {
        cout << "원하시는 메뉴를 입력해주세요" << "\n";
        cout << "1. 원화 -> 외화" << "\n";
        cout << "2. 외화 -> 원화" << "\n";
        cout << "3. 종료" << "\n";
        cin >> choose;

        system(CLEAR);

        switch(choose)    {
            case 1: cout << "총 " << exchangeWon() << "\n"; break;
            case 2: cout << "총 " << exchangeOther() << "\n"; break;
            case 3: return 0;
        }
    }
	return 0;
}