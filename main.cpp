#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class URLshortner{
    unordered_map<string,string> ShorttoLong;
    unordered_map<string,string> LongtoShort;
    string chars="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    unordered_map<string,int> clickcount;
    unordered_map<string,time_t> expiryTime;
public:
    URLshortner(){
        loadfromfiles();
        cleanupExpired();
    }
    string generate(){
        string code="";
        for(int i=0;i<6;i++){
            code+=chars[rand()%chars.size()];
        }
        return code;
    }
    string shortner(string longURL,string custom="",int seconds=0){
        if(seconds<0)return "Invalid expiry time";

        if(LongtoShort.find(longURL)!=LongtoShort.end()){
            string oldcode=LongtoShort[longURL];
            if(expiryTime.find(oldcode)!=expiryTime.end() && time(0)>expiryTime[oldcode]){

            LongtoShort.erase(longURL);
            ShorttoLong.erase(oldcode);
            expiryTime.erase(oldcode);
            clickcount.erase(oldcode);
            savetofiles();
            return "Link Expired";

            }else {
            return oldcode;}
        }   
        string code;

        if(custom!=""){
            code=custom;
            if(ShorttoLong.find(custom)!=ShorttoLong.end()){
            return "This alias already exist"; 
            }
        } else { 
            code=generate(); }

        while(ShorttoLong.find(code)!=ShorttoLong.end()){
            code=generate();
        }

        if(seconds>0){
        expiryTime[code]=time(0)+seconds;
        }

        clickcount[code]=0;
        ShorttoLong[code]=longURL;
        LongtoShort[longURL]=code;
        savetofiles();
        return code;
    }

    string getoriginal(string shortURL){
        if(expiryTime.find(shortURL)!=expiryTime.end() && time(0)>expiryTime[shortURL]){
        string longURL = ShorttoLong[shortURL];

        ShorttoLong.erase(shortURL);
        LongtoShort.erase(longURL);
        clickcount.erase(shortURL);
        expiryTime.erase(shortURL);
        savetofiles();

        return "Link Expired";
        }

        if(ShorttoLong.find(shortURL)!=ShorttoLong.end()){
            clickcount[shortURL]++;
            return ShorttoLong[shortURL];
        }

        return "URL not found";
    }

    int getclickcount(string code){
        return clickcount[code];
    }

    void savetofiles(){
        ofstream file("urls.txt");

        for(auto x: ShorttoLong){
            file<<x.first<<" "
                <<x.second<<" "
                <<clickcount[x.first]<<" ";

            if(expiryTime.find(x.first)!=expiryTime.end()){
                file<<expiryTime[x.first];
            } else file<<0;

            file<<endl;
        }
    }

    void loadfromfiles(){
        ifstream file("urls.txt");

        string code,url;
        int clicks;
        time_t expiry;

        while(file>>code>>url>>clicks>>expiry){
            ShorttoLong[code]=url;
            LongtoShort[url]=code;
            clickcount[code]=clicks;
            if(expiry>0) expiryTime[code]=expiry;
        }
    }

    void deleteurl(string code){
        if(ShorttoLong.find(code)==ShorttoLong.end()){
            cout<<"URL not found"<<endl;
            return;
        }

        string longurl=ShorttoLong[code];
        ShorttoLong.erase(code);
        LongtoShort.erase(longurl);
        clickcount.erase(code);
        expiryTime.erase(code);

        savetofiles();
        cout<<"Deleted successfully"<<endl;
        return;
    }

    void analytics(){
        cleanupExpired();

        for(auto x:ShorttoLong){
            cout<<"Short url: "<<x.first<<endl;
            cout<<"Original url: "<<x.second<<endl;
            cout<<"clicks: "<<clickcount[x.first]<<endl;

            if(expiryTime.find(x.first)!=expiryTime.end()){
                    cout<<"Expiry: "<<ctime(&expiryTime[x.first])<<endl;
               
            } else cout<<"Expiry: None"<<endl;

            cout<<"----------------------------------"<<endl;


        }
        return;
    }
    void topclicked(){
        int max=-1;
        string url="";
        for(auto x:ShorttoLong){
            int y=clickcount[x.first];
            if(y>max){ max=y;
                       url=x.first;
        }
        }
        cout<<"Top clicked short URL: "<<url<<endl;
        cout<<"Clicks: "<<max<<endl;
    }
    void cleanupExpired(){
        vector<string> expired;
        for(auto u:ShorttoLong){
            if(expiryTime.find(u.first)!=expiryTime.end() && time(0)>expiryTime[u.first]){
                expired.push_back(u.first);
            }
        }
        for(auto s:expired){
            string l=ShorttoLong[s];
            ShorttoLong.erase(s);
            LongtoShort.erase(l);
            clickcount.erase(s);
            expiryTime.erase(s);
            }
        
        savetofiles();
        return;
    }
};

int main(){
    int choice;
    URLshortner us;
    srand(time(0));

    while(1){
         cout<<"1.Shorten the URL"<<endl;
        cout<<"2.Get original URL"<<endl;
        cout<<"3.Show analytics"<<endl;
        cout<<"4.delete url"<<endl;
        cout<<"5.Top clicked"<<endl;
        cout<<"6.Exit"<<endl;
        cin>>choice;

        if(choice==1){
            string url;
            cout<<"Enter URL: ";
            cin>>url;
            string shortURL;
            cout<<"Want custom aslias? (y/n)"<<endl;
            char c;
            cin>>c;
            if(c=='y'){
                string custom;
                cout<<"Enter alias: ";
                cin>>custom;
                int expiry;
                cout<<"Enter expiry time in seconds (0 for no expiry): ";
                cin>>expiry;
                shortURL=us.shortner(url,custom,expiry);
            }else  if(c=='n'){
                int expiry;
                cout<<"Enter expiry time in seconds (0 for no expiry): ";
                cin>>expiry;
                shortURL=us.shortner(url,"",expiry); 
            }else{ cout<<"Invalid choice";
            break;}
            cout<<"Short URL:"<<shortURL<<endl;
        }

        if(choice==2){
            string code;
            cout<<"Enter short code:";
            cin>>code;
            string longURL=us.getoriginal(code);
            cout<<"Original URL:"<<longURL<<endl;
        }

        if(choice==3){
            us.analytics();
        }

        if(choice==4){
            string code;
            cout<<"Enter short URL to delete: ";
            cin>>code;
            us.deleteurl(code);
        }

        if(choice==5){
            us.topclicked();
        }

        if(choice==6){
            break;
        }
    }
    return 0;
}