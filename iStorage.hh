
#ifndef ISTORAGE
#define ISTORAGE

// One Class to rule them all, One Class to find them
// One Class to bring them all, and in the code bind them
// In the Land of C++ where shadows lie
// ...
// A class to store all the possible ingredients (PDFs, options,...)
// to pass between all the funciotns along all the PEX funciotns...

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

// Possible exotic objects/ingredients:
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TSpline.h"
#include "TObject.h"

// // For identify types:
// #include <typeinfo> // typeid(int); typeid(double); typeid(string).name(); std::type_info& cosa;
// //   inline bool isInt(){ return typeid(iTObject)==typeid(int);}
// //   inline bool isDouble(){ return typeid(iTObject)==typeid(double);}
// //   inline bool isString(){ return typeid(iTObject)==typeid(string);}
// template<typename T1, typename T2>
// inline string mapType(map<T1,T2> m){
//   if(typeid(m)==typeid(mapTH1)) return "TH1";
//   if(typeid(m)==typeid(mapTH2)) return "TH2";
//   if(typeid(m)==typeid(mapTH3)) return "TH3";
//   if(typeid(m)==typeid(mapdouble)) return "double";
//   if(typeid(m)==typeid(mapbool)) return "bool";
//   if(typeid(m)==typeid(mapstring)) return "string";
//   if(typeid(m)==typeid(mapTF1)) return "TF1";
//   if(typeid(m)==typeid(mapTObject)) return "TObject";
//   if(typeid(m)==typeid(mapTSpline3)) return "TSpline3";
//   if(typeid(m)==typeid(mapRules)) return "rule";
//   return "unknown";
// }

using namespace std;

struct iStorage : public TObject{

  map<string,string>    mapAllKeys;//To store all the keys... and its corresponding type/map
  map<string,map<string,string> > mapRules;//To store rules, like the histograms to Normalise, or things to set -> mapRules["string #2, the object name"]["string #1, the rule"]="string #3, the option"
  map<string,TH1*>      mapTH1;
  map<string,TH2*>      mapTH2;
  map<string,TH3*>      mapTH3;
  map<string,TF1*>      mapTF1;
  map<string,TObject*>  mapTObject;
  map<string,TSpline3*> mapTSpline3;
  //map<string,AnyClass > mapAnyClass;
  map<string,double>    mapdouble;
  map<string,bool>      mapbool;
  map<string,string>    mapstring;
  string pname;
  bool pverbose;

  iStorage(string name = "anonymous"){
    pname=name;
    pverbose=true;
  }

  iStorage(iStorage* copy){
    mapAllKeys = copy->mapAllKeys;
    mapRules = copy->mapRules;
    mapTH1 = copy->mapTH1;
    mapTH2 = copy->mapTH2;
    mapTH3 = copy->mapTH3;
    mapTF1 = copy->mapTF1;
    mapTObject = copy->mapTObject;
    mapTSpline3 = copy->mapTSpline3;
    mapdouble = copy->mapdouble;
    mapbool = copy->mapbool;
    mapstring = copy->mapstring;
    pname = copy->pname;
    pverbose = copy->pverbose;
  }

  // ~iStorage(){
  //   delete mapTH1;
  // }

  // A useful function:
  template<typename T1, typename T2, typename T3>
  inline bool existKey(map<T1,T2> m, T3 key){ return m.count(key)!=0; }

  // Setting verbose:
  inline void verbose(bool option){ pverbose=option; }
  inline void verboseON(){ pverbose=true; }
  inline void verboseOFF(){ pverbose=false; }
  inline bool verbose(){ return pverbose; }

  // Setting the iStorage name:
  inline void name (string new_name){ pname = new_name; }
  inline string name(){ return pname; }

  // Writing the iStorage:
  inline int Write(const char *name = 0, Int_t option = 0, Int_t bufsize = 0){
    if(name == 0) return ((const TObject*)this)->Write(pname.c_str(), option, bufsize);
    return ((const TObject*)this)->Write(name, option, bufsize);
  }
  // TODO: A Save and Load functions with ROOT files...

  // Checking existences:
  inline bool isTH1(string name){ return existKey(mapTH1,name); }
  inline bool isTH2(string name){ return existKey(mapTH2,name); }
  inline bool isTH3(string name){ return existKey(mapTH3,name); }
  inline bool isTF1(string name){ return existKey(mapTF1,name); }
  inline bool isTObject(string name){ return existKey(mapTObject,name); }
  inline bool isTSpline3(string name){ return existKey(mapTSpline3,name); }
  inline bool isdouble(string name){ return existKey(mapdouble,name); }
  inline bool isd(string name){ return existKey(mapdouble,name); }
  inline bool isint(string name){ return existKey(mapdouble,name); }
  inline bool isi(string name){ return existKey(mapdouble,name); }
  inline bool isbool(string name){ return existKey(mapbool,name); }
  inline bool isb(string name){ return existKey(mapbool,name); }
  inline bool is(string name){ return existKey(mapbool,name); }
  inline bool est(string name){ return existKey(mapbool,name); }
  inline bool isstring(string name){ return existKey(mapstring,name); }
  inline bool iss(string name){ return existKey(mapstring,name); }
  inline bool exist(string name){ return existKey(mapAllKeys,name); }
  inline bool exists(string name){ return existKey(mapAllKeys,name); }
  inline bool istrue(string name){//Check if the given object exist in the map or false
    if(existKey(mapbool,name)) return mapbool[name];
    return false;
  }
  inline bool isfalse(string name){ return !istrue(name); }
  inline bool isbooltrue(string name){ return istrue(name); }
  inline bool isnot(string name){ return !istrue(name); }
  inline string type(string name){
    if(exist(name)) return mapAllKeys[name];
    else return "unknown";
  }

  //Add functions:
  inline void bruteAddTH1 (string name, TH1* object ){
    mapTH1[name] = object;
    mapAllKeys[name]="TH1";
  }
  inline void bruteAddTH1 (string name, TH1* object, string norm){
    bruteAddTH1(name,object);
    mapRules[name]["norm"] = norm;
    //cout << " > Added TH1 \"" << name << "\" " << endl;
  }
  inline void bruteAddTH2 (string name, TH2* object){
    mapTH2[name] = object;
    mapAllKeys[name]="TH2";
  }
  inline void bruteAddTH2 (string name, TH2* object, string norm){
    bruteAddTH2(name,object);
    mapRules[name]["norm"] = norm;
    //cout << " > Added TH2 \"" << name << "\" " << endl;
  }
  inline void bruteAddTH3 (string name, TH3* object){
    mapTH3[name] = object;
    mapAllKeys[name]="TH3";
  }
  inline void bruteAddTH3 (string name, TH3* object, string norm){
    bruteAddTH3(name,object);
    mapRules[name]["norm"] = norm;
    //cout << " > Added TH3 \"" << name << "\" " << endl;
  }
  inline void bruteAddTF1 (string name, TF1* object ){
    mapTF1[name] = object;
    mapAllKeys[name]="TF1";
    //cout << " > Added TF1 \"" << name << "\" " << endl;
  }
  inline void bruteAddTObject (string name, TObject* object ){
    mapTObject[name] = object;
    mapAllKeys[name]="TObject";
    //cout << " > Added TObject \"" << name << "\" " << endl;
  }
  inline void bruteAddTSpline3 (string name, TSpline3* object ){
    mapTSpline3[name] = object;
    mapAllKeys[name]="TSpline3";
    //cout << " > Added TSpline3 \"" << name << "\" " << endl;
  }
  inline void bruteAdddouble (string name, double object ){
    mapdouble[name] = object;
    mapAllKeys[name]="double";
    //cout << " > Added double \"" << name << "\": " << object << " " << endl;
  }
  inline void bruteAddbool (string name, bool object ){
    mapbool[name] = object;
    mapAllKeys[name]="bool";
    //cout << " > Added bool \"" << name << "\": " << ((object)?("true"):("false")) << " " << endl;
  }
  inline void bruteAddstring (string name, string object ){
    mapstring[name] = object;
    mapAllKeys[name]="string";
    //cout << " > Added string \"" << name << "\": \"" << object << "\" " << endl;
  }
  void addTH1 (string name, TH1* object, string norm = "width" ){
    if(!exist(name)){
      bruteAddTH1(name,object,norm);
    }else if(verbose()) cout << " >>> ERROR: (TH1) \"" << name << "\" not added because already exists as (" << mapAllKeys[name] << ") type!" << endl;
  }
  void addTH2 (string name, TH2* object, string norm = "width" ){
    if(!exist(name)){
      bruteAddTH2(name,object,norm);
    }else if(verbose()) cout << " >>> ERROR: (TH2) \"" << name << "\" not added because already exists as (" << mapAllKeys[name] << ") type!" << endl;
  }
  void addTH3 (string name, TH3* object, string norm = "width" ){
    if(!exist(name)){
      bruteAddTH3(name,object,norm);
    }else if(verbose()) cout << " >>> ERROR: (TH3) \"" << name << "\" not added because already exists as (" << mapAllKeys[name] << ") type!" << endl;
  }
  void addTF1 (string name, TF1* object ){
    if(!exist(name)){
      bruteAddTF1(name,object);
    }else if(verbose()) cout << " >>> ERROR: (TF1) \"" << name << "\" not added because already exists as (" << mapAllKeys[name] << ") type!" << endl;
  }
  void addTObject (string name, TObject* object ){
    if(!exist(name)){
      bruteAddTObject(name,object);
    }else if(verbose()) cout << " >>> ERROR: (TObject) \"" << name << "\" not added because already exists as (" << mapAllKeys[name] << ") type!" << endl;
  }
  void addTSpline3 (string name, TSpline3* object ){
    if(!exist(name)){
      bruteAddTSpline3(name,object);
    }else if(verbose()) cout << " >>> ERROR: (TSpline3) \"" << name << "\" not added because already exists as (" << mapAllKeys[name] << ") type!" << endl;
  }
  void adddouble (string name, double object ){
    if(!exist(name)){
      bruteAdddouble(name,object);
    }else if(verbose()) cout << " >>> ERROR: (double) \"" << name << "\" not added because already exists as (" << mapAllKeys[name] << ") type!" << endl;
  }
  void addbool (string name, bool object ){
    if(!exist(name)){
      bruteAddbool(name,object);
    }else if(verbose()) cout << " >>> ERROR: (bool) \"" << name << "\" not added because already exists as (" << mapAllKeys[name] << ") type!" << endl;
  }
  void addstring (string name, string object ){
    if(!exist(name)){
      bruteAddstring(name,object);
    }else if(verbose()) cout << " >>> ERROR: (string) \"" << name << "\" not added because already exists as (" << mapAllKeys[name] << ") type!" << endl;
  }
  void adds (string name, string object ){ addstring(name,object); }

  //Overloaded add functions:
  void add (string name, TH1* object, string norm = "width" ){ addTH1(name,object,norm); }
  void add (string name, TH2* object, string norm = "width" ){ addTH2(name,object,norm); }//For some weird reason beyond my understanding Python cannot use it...
  void add (string name, TH3* object, string norm = "width" ){ addTH3(name,object,norm); }//For some weird reason beyond my understanding Python cannot use it...
  void add (string name, TF1* object ){ addTF1(name,object); }
  void add (string name, TObject* object ){ addTObject(name,object); }
  void add (string name, TSpline3* object ){ addTSpline3(name,object); }
  void add (string name, double object ){ adddouble(name,object); }
  //void add (string name, int object ){ adddouble(name,object); }//For another weird reason, I need to comment this or will overwrite previous add(double) function
  void add (string name, bool object ){ addbool(name,object); }
  void add (string name, string object ){
    if(object=="true" || object=="True") addbool(name,true);
    else if(object=="false" || object=="False") addbool(name,false);
    else addstring(name,object);
  }

  //Set functions:
  inline void setTH1 (string name, TH1* object, string norm = "nessuno" ){
    if(!exist(name)){
      if(norm!="nessuno") addTH1(name,object,norm);
      else addTH1(name,object);
    }else if(isTH1(name)){
      if(norm!="nessuno") bruteAddTH1(name,object,norm);
      else bruteAddTH1(name,object);
    }else if(verbose()) cout << " >>> ERROR: (TH1) \"" << name << "\" not setted because already exists as (" << mapAllKeys[name] << ") type!" << endl;
  }
  inline void setTH2 (string name, TH2* object, string norm = "nessuno" ){
    if(!exist(name)){
      if(norm!="nessuno") addTH2(name,object,norm);
      else addTH2(name,object);
    }else if(isTH2(name)){
      if(norm!="nessuno") bruteAddTH2(name,object,norm);
      else bruteAddTH2(name,object);
    }else if(verbose()) cout << " >>> ERROR: (TH2) \"" << name << "\" not setted because already exists as (" << mapAllKeys[name] << ") type!" << endl;
  }
  inline void setTH3 (string name, TH3* object, string norm = "nessuno" ){
    if(!exist(name)){
      if(norm!="nessuno") addTH3(name,object,norm);
      else addTH3(name,object);
    }else if(isTH3(name)){
      if(norm!="nessuno") bruteAddTH3(name,object,norm);
      else bruteAddTH3(name,object);
    }else if(verbose()) cout << " >>> ERROR: (TH3) \"" << name << "\" not setted because already exists as (" << mapAllKeys[name] << ") type!" << endl;
  }
  inline void setTF1 (string name, TF1* object ){
    if(!exist(name)){
      addTF1(name,object);
    }else if(isTF1(name)){
      bruteAddTF1(name,object);
    }else if(verbose()) cout << " >>> ERROR: (TF1) \"" << name << "\" not setted because already exists as (" << mapAllKeys[name] << ") type!" << endl;
  }
  inline void setTObject  (string name, TObject*  object ){
    if(!exist(name)){
      addTObject(name,object);
    }else if(isTObject(name)){
      bruteAddTObject(name,object);
    }else if(verbose()) cout << " >>> ERROR: (TObject) \"" << name << "\" not setted because already exists as (" << mapAllKeys[name] << ") type!" << endl;
  }
  inline void setTSpline3 (string name, TSpline3* object ){
    if(!exist(name)){
      addTSpline3(name,object);
    }else if(isTSpline3(name)){
      bruteAddTSpline3(name,object);
    }else if(verbose()) cout << " >>> ERROR: (TSpline3) \"" << name << "\" not setted because already exists as (" << mapAllKeys[name] << ") type!" << endl;
  }
  inline void setdouble (string name, double object ){
    if(!exist(name)){
      adddouble(name,object);
    }else if(isdouble(name)){
      bruteAdddouble(name,object);
    }else if(verbose()) cout << " >>> ERROR: (double) \"" << name << "\" not setted because already exists as (" << mapAllKeys[name] << ") type!" << endl;
  }
  inline void setd (string name, double object ){ setdouble(name,object); }
  inline void setn (string name, double object ){ setdouble(name,object); }
  inline void seti (string name, int object ){ setdouble(name,object); }
  inline void setbool (string name, bool object ){
    if(!exist(name)){
      addbool(name,object);
    }else if(isbool(name)){
      bruteAddbool(name,object);
    }else if(verbose()) cout << " >>> ERROR: (bool) \"" << name << "\" not setted because already exists as (" << mapAllKeys[name] << ") type!" << endl;
  }
  inline void setb (string name, bool object ){ setbool(name,object); }
  inline void setb (string name ){ setbool(name,true); }
  inline void setstring (string name, string object ){
    if(!exist(name)){
      addstring(name,object);
    }else if(isstring(name)){
      bruteAddstring(name,object);
    }else if(verbose()) cout << " >>> ERROR: (string) \"" << name << "\" not setted because already exists as (" << mapAllKeys[name] << ") type!" << endl;
  }
  inline void sets (string name, string object ){ setstring(name,object); }

  //Overloaded set functions:
  inline void set (string name, TH1* object, string norm = "width" ){ setTH1(name,object,norm); }
  inline void set (string name, TH2* object, string norm = "width" ){ setTH2(name,object,norm); }//For some weird reason beyond my understanding Python cannot use it...
  inline void set (string name, TH3* object, string norm = "width" ){ setTH3(name,object,norm); }//For some weird reason beyond my understanding Python cannot use it...
  inline void set (string name, TF1* object ){ setTF1(name,object); }
  inline void set (string name, TObject* object ){ setTObject(name,object); }
  inline void set (string name, TSpline3* object ){ setTSpline3(name,object); }
  inline void set (string name, double object ){ setdouble(name,object); }
  //inline void set (string name, int object ){ setdouble(name,object); }//For another weird reason, I need to comment this or will overwrite previous set(double) function
  inline void set (string name, bool object ){ setbool(name,object); }//For some weird reason beyond my understanding Python cannot pass a boolean OR an int to C++, both are treated the same: so if set(int) is defined a boolean passed to set() will not be treated by set(bool) but by set(int); and without set(int) defined, an int = 0 is treated by set(bool) not by set(double); I have to overload the set(string)...
  inline void set (string name ){ setbool(name,true); }
  inline void set (string name, string object ){
    if(object=="true" || object=="True") setbool(name,true);
    else if(object=="false" || object=="False") setbool(name,false);
    else setstring(name,object);
  }

  //Get functions. ATENTION: Optimised code! i.e. do not check if the entry exists!
  inline TH1* getTH1 (string name){ return mapTH1[name]; }
  inline TH2* getTH2 (string name){ return mapTH2[name]; }
  inline TH3* getTH3 (string name){ return mapTH3[name]; }
  inline TF1* getTF1 (string name){ return mapTF1[name]; }
  inline TObject* getTObject (string name){ return mapTObject[name]; }
  inline TSpline3* getTSpline3 (string name){ return mapTSpline3[name]; }
  inline double getdouble (string name){ return mapdouble[name]; }
  inline int getint (string name){ return int(mapdouble[name]); }
  inline bool getbool (string name){ return mapbool[name]; }
  inline string getstring (string name){ return mapstring[name]; }
  inline double getd (string name){ return mapdouble[name]; }
  inline double getn (string name){ return mapdouble[name]; }
  inline int    geti (string name){ return int(mapdouble[name]); }
  inline bool   getb (string name){ return mapbool[name]; }
  inline string gets (string name){ return mapstring[name]; }
  inline double get  (string name){ return mapdouble[name]; }//No way to overload the return type... this is the default one

  //Safe get functions. Check if the entry exists:
  inline TH1* sgetTH1 (string name){ if(isTH1(name)) return mapTH1[name]; else if(verbose()){ cout << " >>> ERROR: (TH1) \"" << name << "\" does not exists!"; if(exist(name)) cout << " ...it seems to be defined as (" << type(name) << ")"; cout << endl;} }
  inline TH2* sgetTH2 (string name){ if(isTH2(name)) return mapTH2[name]; else if(verbose()){ cout << " >>> ERROR: (TH2) \"" << name << "\" does not exists!"; if(exist(name)) cout << " ...it seems to be defined as (" << type(name) << ")"; cout << endl;} }
  inline TH3* sgetTH3 (string name){ if(isTH3(name)) return mapTH3[name]; else if(verbose()){ cout << " >>> ERROR: (TH3) \"" << name << "\" does not exists!"; if(exist(name)) cout << " ...it seems to be defined as (" << type(name) << ")"; cout << endl;} }
  inline TF1* sgetTF1 (string name){ if(isTF1(name)) return mapTF1[name]; else if(verbose()){ cout << " >>> ERROR: (TF1) \"" << name << "\" does not exists!"; if(exist(name)) cout << " ...it seems to be defined as (" << type(name) << ")"; cout << endl;} }
  inline TObject* sgetTObject (string name){ if(isTObject(name)) return mapTObject[name]; else if(verbose()){ cout << " >>> ERROR: (TObject) \"" << name << "\" does not exists!"; if(exist(name)) cout << " ...it seems to be defined as (" << type(name) << ")"; cout << endl;} }
  inline TSpline3* sgetTSpline3 (string name){ if(isTSpline3(name)) return mapTSpline3[name]; else if(verbose()){ cout << " >>> ERROR: (TSpline3) \"" << name << "\" does not exists!"; if(exist(name)) cout << " ...it seems to be defined as (" << type(name) << ")"; cout << endl;} }
  inline double sgetdouble (string name){ if(isdouble(name)) return mapdouble[name]; else if(verbose()){ cout << " >>> ERROR: (double) \"" << name << "\" does not exists!"; if(exist(name)) cout << " ...it seems to be defined as (" << type(name) << ")"; cout << endl;} }
  inline int sgetint (string name){ if(isdouble(name)) return int(mapdouble[name]); else if(verbose()){ cout << " >>> ERROR: (double) \"" << name << "\" does not exists!"; if(exist(name)) cout << " ...it seems to be defined as (" << type(name) << ")"; cout << endl;} }
  inline bool sgetbool (string name){ if(isbool(name)) return mapbool[name]; else if(verbose()){ cout << " >>> ERROR: (bool) \"" << name << "\" does not exists!"; if(exist(name)) cout << " ...it seems to be defined as (" << type(name) << ")"; cout << endl;} }
  inline string sgetstring (string name){ if(isstring(name)) return mapstring[name]; else if(verbose()){ cout << " >>> ERROR: (string) \"" << name << "\" does not exists!"; if(exist(name)) cout << " ...it seems to be defined as (" << type(name) << ")"; cout << endl;} }
  inline double sgetd (string name){ if(isdouble(name)) return mapdouble[name]; else if(verbose()){ cout << " >>> ERROR: (double) \"" << name << "\" does not exists!"; if(exist(name)) cout << " ...it seems to be defined as (" << type(name) << ")"; cout << endl;} }
  inline double sgetn (string name){ if(isdouble(name)) return mapdouble[name]; else if(verbose()){ cout << " >>> ERROR: (double) \"" << name << "\" does not exists!"; if(exist(name)) cout << " ...it seems to be defined as (" << type(name) << ")"; cout << endl;} }
  inline int    sgeti (string name){ if(isdouble(name)) return int(mapdouble[name]); else if(verbose()){ cout << " >>> ERROR: (double) \"" << name << "\" does not exists!"; if(exist(name)) cout << " ...it seems to be defined as (" << type(name) << ")"; cout << endl;} }
  inline bool   sgetb (string name){ if(isbool(name)) return mapbool[name]; else if(verbose()){ cout << " >>> ERROR: (bool) \"" << name << "\" does not exists!"; if(exist(name)) cout << " ...it seems to be defined as (" << type(name) << ")"; cout << endl;} }
  inline string sgets (string name){ if(isstring(name)) return mapstring[name]; else if(verbose()){ cout << " >>> ERROR: (string) \"" << name << "\" does not exists!"; if(exist(name)) cout << " ...it seems to be defined as (" << type(name) << ")"; cout << endl;} }
  inline double sget  (string name){ if(isdouble(name)) return mapdouble[name]; else if(verbose()){ cout << " >>> ERROR: (double) \"" << name << "\" does not exists!"; if(exist(name)) cout << " ...it seems to be defined as (" << type(name) << ")"; cout << endl;} }//No way to overload the return type... this is the default one

  // Normalisation routines for the ingredients that allow it:
  void normalise (){//Will normalise all the histograms except the ones that were added by add(name,object,false)
    if(verbose()) cout << "  --    Normalising histograms...";
    for( map<string,map<string,string> >::iterator it = mapRules.begin() ; it != mapRules.end(); it++ ){
      // it->first="h_time"
      // it->second["norm"]="width"
      if(existKey(it->second,"norm")){
        if(existKey(mapTH1,it->first)){
          if(it->second["norm"]=="width") mapTH1[it->first]->Scale( 1.0 / mapTH1[it->first]->Integral("width") );
          else mapTH1[it->first]->Scale( 1.0 / mapTH1[it->first]->Integral() );
        }else if(existKey(mapTH2,it->first)){
          if(it->second["norm"]=="width") mapTH2[it->first]->Scale( 1.0 / mapTH2[it->first]->Integral("width") );
          else mapTH2[it->first]->Scale( 1.0 / mapTH2[it->first]->Integral() );
          //if(it->second["norm"]=="X") TODO: Normalise along X for each Y channel
          //else if(it->second["norm"]=="Y") TODO: Normalise along Y for each X channel
        }else if(existKey(mapTH3,it->first)){
          if(it->second["norm"]=="width") mapTH3[it->first]->Scale( 1.0 / mapTH3[it->first]->Integral("width") );
          else mapTH3[it->first]->Scale( 1.0 / mapTH3[it->first]->Integral() );
          //if(it->second["norm"]=="XY") TODO: Normalise plane XY for each Z channel
          //else if(it->second["norm"]=="YZ") TODO: Normalise plane YZ for each X channel
          //else if(it->second["norm"]=="XZ") TODO: Normalise plane XZ for each Y channel
          //else if(it->second["norm"]=="X") TODO: Normalise along X for each YZ plane
          //else if(it->second["norm"]=="Y") TODO: Normalise along Y for each XZ plane
          //else if(it->second["norm"]=="Z") TODO: Normalise along Z for each XY plane
        }
        if(verbose()) cout << "    " << mapAllKeys[it->first] << " " << it->first << ": " << ((it->second["norm"]=="width")?("width Normalised"):("Normalised")) << endl;
      }else if(verbose()) cout << "    " << mapAllKeys[it->first] << " " << it->first << ": not Normalised" << endl;

    }
    if(verbose()) cout << " Done!" << endl;
    return;
  } void normalize (){ normalise(); }

  inline void wtf(string message = "WTF!"){ cout << "\n" << message << "\n"; }

  //This function will present all the contents stored:
  void show(){
    cout << "  ==========================================================================\n  || \n  ||  > Contents in the iStorage \"" << pname << "\":" << endl;
    //First I will Normalise as much as I can:
    normalise();
    //The TH1:
    if(mapTH1.begin()!=mapTH1.end()){
      cout << "  || \n  ||    TH1:" << endl;
      for( map<string,TH1*>::iterator it = mapTH1.begin() ; it != mapTH1.end(); it++ ){
        cout << "  ||     - " << it->first << ":" << endl
             << "  ||        (title)  \"" << it->second->GetTitle() << "\"  [" << ((mapRules["norm"][it->first].find("none") == string::npos)?((mapRules["norm"][it->first].find("width") == string::npos)?("Width N"):("N")):("Not n")) << "ormalized -> " << it->second->Integral() << "]" << endl
             << "  ||        (X axis) \"" << it->second->GetXaxis()->GetTitle() << "\" (" << it->second->GetXaxis()->GetBinLowEdge(1) << "," << it->second->GetXaxis()->GetBinUpEdge(it->second->GetXaxis()->GetNbins()) << "; " << it->second->GetXaxis()->GetNbins() << " bins -> " << (it->second->GetXaxis()->GetBinUpEdge(it->second->GetXaxis()->GetNbins())-it->second->GetXaxis()->GetBinLowEdge(1))/it->second->GetXaxis()->GetNbins() << ")" << endl;
      }
    }
    //The TH2:
    if(mapTH2.begin()!=mapTH2.end()){
      cout << "  || \n  ||    TH2:" << endl;
      for( map<string,TH2*>::iterator it = mapTH2.begin() ; it != mapTH2.end(); it++ ){
        cout << "  ||     - " << it->first << ":" << endl
             << "  ||        (title)  \"" << it->second->GetTitle() << "\"  [" << ((mapRules["norm"][it->first].find("none") == string::npos)?((mapRules["norm"][it->first].find("width") == string::npos)?("Width N"):("N")):("Not n")) << "ormalized -> " << it->second->Integral() << "]" << endl
             << "  ||        (X axis) \"" << it->second->GetXaxis()->GetTitle() << "\" (" << it->second->GetXaxis()->GetBinLowEdge(1) << "," << it->second->GetXaxis()->GetBinUpEdge(it->second->GetXaxis()->GetNbins()) << "; " << it->second->GetXaxis()->GetNbins() << " bins -> " << (it->second->GetXaxis()->GetBinUpEdge(it->second->GetXaxis()->GetNbins())-it->second->GetXaxis()->GetBinLowEdge(1))/it->second->GetXaxis()->GetNbins() << ")" << endl
             << "  ||        (Y axis) \"" << it->second->GetYaxis()->GetTitle() << "\" (" << it->second->GetYaxis()->GetBinLowEdge(1) << "," << it->second->GetYaxis()->GetBinUpEdge(it->second->GetYaxis()->GetNbins()) << "; " << it->second->GetYaxis()->GetNbins() << " bins -> " << (it->second->GetYaxis()->GetBinUpEdge(it->second->GetYaxis()->GetNbins())-it->second->GetYaxis()->GetBinLowEdge(1))/it->second->GetYaxis()->GetNbins() << ")" << endl;
      }
    }
    //The TH3:
    if(mapTH3.begin()!=mapTH3.end()){
      cout << "  || \n  ||    TH3:" << endl;
      for( map<string,TH3*>::iterator it = mapTH3.begin() ; it != mapTH3.end(); it++ ){
        cout << "  ||     - " << it->first << ":" << endl
             << "  ||        (title)  \"" << it->second->GetTitle() << "\"  [" << ((mapRules["norm"][it->first].find("none") == string::npos)?((mapRules["norm"][it->first].find("width") == string::npos)?("Width N"):("N")):("Not n")) << "ormalized -> " << it->second->Integral() << "]" << endl
             << "  ||        (X axis) \"" << it->second->GetXaxis()->GetTitle() << "\" (" << it->second->GetXaxis()->GetBinLowEdge(1) << "," << it->second->GetXaxis()->GetBinUpEdge(it->second->GetXaxis()->GetNbins()) << ") [ " << it->second->GetXaxis()->GetNbins() << " bins -> " << (it->second->GetXaxis()->GetBinUpEdge(it->second->GetXaxis()->GetNbins())-it->second->GetXaxis()->GetBinLowEdge(1))/it->second->GetXaxis()->GetNbins() << " ]" << endl
             << "  ||        (Y axis) \"" << it->second->GetYaxis()->GetTitle() << "\" (" << it->second->GetYaxis()->GetBinLowEdge(1) << "," << it->second->GetYaxis()->GetBinUpEdge(it->second->GetYaxis()->GetNbins()) << ") [ " << it->second->GetYaxis()->GetNbins() << " bins -> " << (it->second->GetYaxis()->GetBinUpEdge(it->second->GetYaxis()->GetNbins())-it->second->GetYaxis()->GetBinLowEdge(1))/it->second->GetYaxis()->GetNbins() << " ]" << endl
             << "  ||        (Z axis) \"" << it->second->GetZaxis()->GetTitle() << "\" (" << it->second->GetZaxis()->GetBinLowEdge(1) << "," << it->second->GetZaxis()->GetBinUpEdge(it->second->GetZaxis()->GetNbins()) << ") [ " << it->second->GetZaxis()->GetNbins() << " bins -> " << (it->second->GetZaxis()->GetBinUpEdge(it->second->GetZaxis()->GetNbins())-it->second->GetZaxis()->GetBinLowEdge(1))/it->second->GetZaxis()->GetNbins() << " ]" << endl;
      }
    }
    //The TF1:
    if(mapTF1.begin()!=mapTF1.end()){
      cout << "  || \n  ||    TF1:" << endl;
      for( map<string,TF1*>::iterator it = mapTF1.begin() ; it != mapTF1.end(); it++ ){
        cout << "  ||     - " << it->first << ": (name) \"" << it->second->GetName() << "\"" << endl
             << "  ||        (range)  [" << it->second->GetXmin() << "," << it->second->GetXmax() << "]" << endl
             << "  ||        (# par)  " << it->second->GetNpar() << "" << endl
             << "  ||        (points) " << it->second->GetNpx() << "" << endl;
      }
    }
    //The TObject:
    if(mapTObject.begin()!=mapTObject.end()){
      cout << "  || \n  ||    TObject:" << endl;
      for( map<string,TObject*>::iterator it = mapTObject.begin() ; it != mapTObject.end(); it++ ){
        cout << "  ||     - " << it->first << ": Nothing to show?" << endl;
      }
    }
    //The TSpline3:
    if(mapTSpline3.begin()!=mapTSpline3.end()){
      cout << "  || \n  ||    TSpline3:" << endl;
      for( map<string,TSpline3*>::iterator it = mapTSpline3.begin() ; it != mapTSpline3.end(); it++ ){
        cout << "  ||     - " << it->first << ": Nothing to show?" << endl;
      }
    }
    //The string, double and bool:
    if(mapstring.begin()!=mapstring.end() || mapdouble.begin()!=mapdouble.end() || mapbool.begin()!=mapbool.end()){
      cout << "  || \n  ||    Parameters:" << endl;
      for( map<string,string>::iterator it = mapstring.begin() ; it != mapstring.end(); it++ ){
        cout << "  ||     - (" << mapAllKeys[it->first] << ")" << it->first << ": \"" << it->second << "\"" << endl;
      }
      for( map<string,double>::iterator it = mapdouble.begin() ; it != mapdouble.end(); it++ ){
        cout << "  ||     - (" << mapAllKeys[it->first] << ")" << it->first << ": " << it->second << "" << endl;
      }
      for( map<string,bool>::iterator it = mapbool.begin() ; it != mapbool.end(); it++ ){
        cout << "  ||     - (" << mapAllKeys[it->first] << ")" << it->first << ": " << ((it->second)?("True"):("False")) << "" << endl;
      }
    }
    cout << "  || " << endl << "  ==========================================================================" << endl;
    return;
  }

  void help() {
    cout << "" << endl;
    cout << " # The most important information about iStorage # " << endl;
    cout << "" << endl;
    cout << " > Implemented TYPES:" << endl;
    cout << "    TH1" << endl;
    cout << "    TH2" << endl;
    cout << "    TH3" << endl;
    cout << "    TF1" << endl;
    cout << "    TObject" << endl;
    cout << "    TSpline3" << endl;
    cout << "    double" << endl;
    cout << "    bool" << endl;
    cout << "    string" << endl;
    cout << "" << endl;
    cout << " > Functions for add/set things:" << endl;
    cout << "    void addTYPE(string, TYPE)" << endl;
    cout << "    void add(string, TYPE)     -> avoid for TH2 and TH3 in Python (use addTYPE)" << endl;
    cout << "    void setTYPE(string, TYPE)" << endl;
    cout << "    void setn(string, double)" << endl;
    cout << "    void set(string, TYPE)     -> avoid for TH2, TH3 and double in Python (use setTYPE)" << endl;
    cout << "    void set(string)           -> for boolean" << endl;
    cout << "" << endl;
    cout << " > For check things:" << endl;
    cout << "    bool isTYPE(string)  -> if a given entry exists" << endl;
    cout << "    bool exists(string)  -> if a given entry exists" << endl;
    cout << "    bool istrue(string)  -> for a boolean setting" << endl;
    cout << "    bool isfalse(string) -> for a boolean setting" << endl;
    cout << "    string type(string)  -> return the type of the key" << endl;
    cout << "" << endl;
    cout << " > For retrieve things:" << endl;
    cout << "    string GetName()" << endl;
    cout << "    double get(string)" << endl;
    cout << "    string gets(string)" << endl;
    cout << "    TH1    getTH1(string)" << endl;
    cout << "    TH2    getTH2(string)" << endl;
    cout << "    TH2    getTH3(string)" << endl;
    cout << "" << endl;
    cout << " > Other functions:" << endl;
    cout << "    void name(string) -> to baptise the iStorage" << endl;
    cout << "    void normalise()  -> to normalise the TH1, TH2 and TH3 according to the rule \"norm\"" << endl;
    cout << "    void show()       -> list all the contents" << endl;
    cout << "    void help()       -> show this" << endl;
    cout << "" << endl;
  }

  ClassDef(iStorage,1)
};

#endif
