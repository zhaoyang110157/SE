#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <bitset>
#include <map>
#include <vector>
using namespace std;

struct HuffmanNode{
  int weight;
  char c;
  HuffmanNode *lhs;
  HuffmanNode *rhs;
  HuffmanNode(int a,char b)
  {
    weight = a;
    c = b; 
    lhs=rhs=NULL;
  }
  HuffmanNode(int a,char b, HuffmanNode* l , HuffmanNode* r)
  {
    weight = a;
    c = b;
    lhs = l;
    rhs = r;
  }
};

HuffmanNode *head;

void naiveCopy(string inputFilename, string outputFilename) {
  ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
  ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
  char c;
  while (ifs.get(c)) ofs.put(c);
  ofs.close();
  ifs.close();
}

void makehufnode(ofstream &ofs ,map<char,int> &firstcheck, multimap< int , HuffmanNode*  > &tmpmulti , bool flag)
{
  map<char,int>::iterator it = firstcheck.begin();
  while( it != firstcheck.end() )
  {
    HuffmanNode *tmp = new HuffmanNode(it->second,it->first);
    cout<<"make Huff : "<<it->second <<" & "<<it->first<<endl ;
    if( flag ) ofs<< it -> first  << it->second <<" ";
    tmpmulti.insert ( make_pair ( it->second , tmp ));
    ++it;
  }
}
void buildhuff(multimap< int , HuffmanNode* > &tmpmulti )
{
  while( tmpmulti.size() >= 2)
  {
    multimap< int , HuffmanNode* >::iterator it = tmpmulti.begin();
    HuffmanNode *tmpl = it->second;
    it++;
    HuffmanNode *tmpr = it->second;
    cout<<"lhs : "<<tmpl->c<<"  rhs : "<<tmpr->c<<endl;
    tmpmulti.erase(it);
    tmpmulti.erase(--it);
    HuffmanNode *tmp  = new HuffmanNode( tmpl->weight+tmpr->weight , '\0' , tmpl , tmpr);
    tmpmulti.insert(make_pair(tmpl->weight+tmpr->weight,tmp));
  }
}

void make_dic( HuffmanNode* Head ,map<char,string > &dictionary , string tmp)
{
  if( Head->lhs == NULL && Head->rhs ==NULL )
  {
    dictionary.insert( make_pair( Head->c , tmp ));
    cout<<"dictionary : "<< Head->c <<" @ "<<tmp<<endl;
    return;
  }
  tmp+="0";
  make_dic( Head->lhs , dictionary , tmp );
  tmp[tmp.size()-1] = '1';
  make_dic( Head->rhs , dictionary , tmp );
}

void make_dict( HuffmanNode* Head ,map<string,char> &dictionary ,string tmp)
{
  if( Head->lhs == NULL && Head->rhs ==NULL )
  {
    dictionary.insert( make_pair( tmp , Head->c ));
    cout<<"dictionary : "<<tmp<<" & "<<Head->c<<endl;
    return;
  }
  tmp+="0";
  make_dict( Head->lhs , dictionary , tmp );
  tmp[tmp.size()-1] = '1';
  make_dict( Head->rhs , dictionary , tmp );
}
void compress(string inputFilename, string outputFilename) {

  ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
  ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
  map<char,int> firstcheck;
  char c;
  while( ifs.get(c) )
  {
    if( firstcheck.find(c) == firstcheck.end() )
    {
      firstcheck.insert( make_pair( c, 1));
      cout<<"first_check : "<<c<<endl;
    }
    else{
      firstcheck[c]+=1;
    }
  } 

  ifs.close();

  if( firstcheck.size() == 0 ){
    return;
    cout<<" cover the empty"<<endl;
  }

  ofs<<'Y'<<firstcheck.size()<<" ";
  cout<<"press the size:"<<firstcheck.size()<<endl;

  multimap< int , HuffmanNode*> tmpmulti;
  makehufnode( ofs , firstcheck , tmpmulti , true );
  cout<<" make them HuffmanNode and press the table "<<endl;

  
  buildhuff( tmpmulti );
  head = tmpmulti.begin()->second;
  cout<<"build the tree"<<endl;
  ofs<<head->weight<<" ";
  map<char,string>  dictionary;
  string tmp;
  make_dic( head , dictionary , tmp );
  cout<<"make the dictionary"<<endl;
  
  ifs.open(inputFilename.c_str(), ios::in | ios::binary);
  string bits = "";
  while(ifs.get(c))
  {
    
      bits += dictionary[c];

    while(bits.length() >= 8) {
      for(int i=0;i<8;++i)
      {
        cout<<bits[i];
      }
			bitset<8> temp(bits.substr(0, 8));
			if (bits.length() == 8)
				bits = "";
			else
				bits = bits.substr(8);
			char temp_int8 = char(temp.to_ulong());
			ofs.write(reinterpret_cast<char*>(&temp_int8), 1);
		}
  }
  cout<< "zip"<<endl;

	if (bits != "") {
		bits += "0000000";
		bitset<8> temp(bits.substr(0, 8));
		char temp_int8 = char(temp.to_ulong());
		ofs.write(reinterpret_cast<char*>(&temp_int8), sizeof(char));
		bits = "";
	} cout<<"last string utput_file"<<endl;

	ifs.close();
	ofs.close();
};

void decompress(string inputFilename, string outputFilename) {
  int num;
  char tmp;
  ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
  ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
  ifs.get(tmp);
  if(tmp!='Y') return;
  if( ifs.eof() ) return;
  ifs >> num;
  cout<<"get the size: "<<num<<endl;
  char ch;
  int weight;
  map<char,int> firstcheck;
  while( num )
  {
    ifs.get(tmp);
    ifs.get(ch);
    ifs >> weight;
    firstcheck.insert( make_pair(ch,weight) );
    num--;
  }
  ifs.get(tmp);
  int allch;
  ifs>>allch;
  ifs.get(tmp);
  cout<<"weight insert"<<endl;

  multimap< int , HuffmanNode*  > tmpmulti;
  makehufnode( ofs , firstcheck , tmpmulti , false );
  cout<<"make the node without press the table"<<endl;

  buildhuff( tmpmulti );
  head = tmpmulti.begin()->second;
  cout<< "build the tree"<<endl;


  map<string , char > dictionary;
  string tmpv;

  make_dict ( head , dictionary , tmpv);
  cout<<"make the dictionary"<<endl;

  string compare = "";
	string buf = "";
  char get_char;
  int i=0;
	while(i<allch) {
    if(ifs.eof()) break;
		if (buf.length() == 0) {
			ifs.get(get_char);
			bitset<8> get_bits(get_char);
			buf += get_bits.to_string();
		}
		if (dictionary.find(compare) != dictionary.end()) {	// find it
      i++;
			ofs.write(reinterpret_cast<char*>(&(dictionary[compare])), sizeof(char));
			ofs.flush();
			compare = "";
		}
		else {	// not find
			compare += buf[0];
			if (buf.length() == 1)
				buf = "";
			else
				buf = buf.substr(1);
		}
  }
}

void usage(string prog) {
	cerr << "Useage: " << endl
		<< "    " << prog << "[-d] input_file output_file" << endl;
	exit(2);
}


int main(int argc, char* argv[]) {
  int i;
  string inputFilename, outputFilename;
  bool isDecompress = false;
  for (i = 1; i < argc; i++) {
    if (argv[i] == string("-d")) isDecompress = true;
    else if (inputFilename == "") inputFilename = argv[i];
    else if (outputFilename == "") outputFilename = argv[i];
    else usage(argv[0]);
  }
  if (outputFilename == "") usage(argv[0]);
  if (isDecompress) decompress(inputFilename, outputFilename);
  else compress(inputFilename, outputFilename);
  return 0;
}

//./Compression -d depress.txt result.txt
//./Compression trace01.txt depress.txt