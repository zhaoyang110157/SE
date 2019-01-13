struct Chain
{
	int key;
	int value;
	Chain* pre;
	Chain* next;
	Chain(int _key=-1, int _value=-1)
	//没有的话会返回-1,可以直接把值设置为-1
	{
		key=_key;
		value=_value;
		pre=NULL;
		next=NULL;
	}
};

class LRUCache
{
private:
	int capacity;
	int size;
	Chain* head;
	Chain* tail;
	map<int,Chain*> address;
public:
	LRUCache(int _capacity)
	{
		capacity = _capacity;
		size = 0;
		head = new Chain();
		tail = new Chain();
		head->next = tail;
		tail->pre = head;
		address.clear();
		// TODO: your code here
	}
	
	int get(int key)
	{
		map<int,Chain*>::iterator it= address.find(key);
		if(it == address.end())
		{
			return -1;
		}
		else {
			Chain* tmp = it->second;
			//抽出，放到头顶
			tmp->next->pre=tmp->pre;
			tmp->pre->next=tmp->next;
			tmp->pre=head;
			tmp->next=head->next;
			head->next=tmp;
			tmp->next->pre=tmp;
			
			return tmp->value;
			
		}
		// TODO: your code here
	}
	
	void put(int key, int value)
	{
		map<int,Chain*>::iterator it= address.find(key);
		if(it == address.end())
		{
			if(size==capacity)
			{
				Chain* tmp = tail->pre;
				tmp->pre->next = tail;
				tail->pre = tmp->pre;
				--size;
				address.erase(tmp->key);
				delete tmp;
			}
			++size;
			
			Chain* tmp=new Chain(key,value);
		
			tmp->next=head->next;
			tmp->pre=head;
			head->next=tmp;
			tmp->next->pre=tmp;
			address.insert(make_pair(key,tmp));
			
		}
		else {
			Chain* tmp = it->second;
			//抽出，放到头顶
			tmp->next->pre=tmp->pre;
			tmp->pre->next=tmp->next;
			
			tmp->value=value;

			tmp->pre=head;
			tmp->next=head->next;
			head->next=tmp;
			tmp->next->pre=tmp;
			
			
			return;
		}
        // TODO: your code here
    }
};
