struct Chain
{
	int key,value,frequent;
	Chain(int _key = -1, int _val = -1,int _frequent=0)
	{
		frequent=_frequent;
		key = _key;
		value = _val;
	}
};
class LFUCache
{
private:
	int capacity;
	int size;
	int less;
	map<int,Chain*> keytoin;
	map<int,list<Chain*>> fretokey;
	map<int,list<Chain*>::iterator> keytoloc;
public:
    LFUCache(int _capacity)
    {
	    capacity=_capacity;
	    size=less=0;
	    keytoin.clear();
	    fretokey.clear();
	    keytoloc.clear();
        // TODO: your code here
    }

    int get(int key)
    {
	    map<int,Chain*>::iterator it= keytoin.find(key);
	    if(it == keytoin.end())
	    {
		    return -1;
	    }
	    else {
		    Chain* tmp = it->second;
		   
		    fretokey[tmp->frequent].erase(keytoloc[key]);
		   
		    if(fretokey[tmp->frequent].empty())
		    {
			    fretokey.erase(tmp->frequent);
			    if(tmp->frequent==less) ++less;
		    }
				 
		    tmp->frequent+=1;
		    if(fretokey.count(tmp->frequent) == 0)
		    {
			    list<Chain*> li;
			    li.push_back(tmp);
			    fretokey[tmp->frequent]=li;
		    }
		    else fretokey[tmp->frequent].push_back(tmp);
		    
		    keytoloc[tmp->key] = std::prev(fretokey[tmp->frequent].end());
		    return tmp->value;
	    }
        // TODO: your code here
    }

    void put(int key, int value)
    {
	    if(capacity<=0) return;
	    
	    int storeVal = get(key);
	    
	    if(storeVal != -1)
	    {
		    keytoin[key]->value=value;
		    return;
	    }
	    else{
		    Chain* now=new Chain(key,value,1);
		    keytoin[ key ] = now;
		    
		    if(size == capacity)
		     {
			     int outKey = fretokey[less].front()->key;
			     fretokey[less].pop_front();
			     keytoin.erase(outKey);
			     keytoloc.erase(outKey);
			     
			     --size;
			     
			     if(fretokey[less].empty())
			     {
				     if(less>1)
				     {
					     fretokey.erase(less);
				     }
			     }
		     }
		    
		     ++size;
		     less=1;
		     if(fretokey.count(less)==0)
		     {
			     list<Chain*> li;
			     li.push_back(now);
			     fretokey[less]=li;
		     }
		    else
		     {
			     fretokey[less].push_back(now);
		     }
		     keytoloc[key] = std::prev( fretokey[less].end());
	    }
        // TODO: your code here
    }
};
