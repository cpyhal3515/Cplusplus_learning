#ifndef MESSAGE_FOLDER
#define MESSAGE_FOLDER

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<set>

/*---------------------- Message Class ----------------------*/
class Folder;
class Message
{
	friend class Folder;
	friend void swap(Message&, Message&);
	friend void swap(Folder&, Folder&);
public:
	explicit Message(const std::string &str = "") : context(str) {};
	Message(const Message&);
	Message& operator=(const Message&);
	~Message();

	void swap(Message&, Message&);


	void save(Folder&);
	void remove(Folder&);

	void print_debug();

	
private:
	std::string context;
	std::set<Folder*> folders;
	void add_to_folders(const Message&);
	void remove_from_folders();

	void addFldr(Folder* f) { folders.insert(f); }
	void remFlddr(Folder* f) { folders.erase(f); }
};

void Message::save(Folder& f)
{
	folders.insert(&f);
	f.addMsg(this);
}
void Message::remove(Folder& f)
{
	folders.erase(&f);
	f.remMsg(this);
}

void Message::add_to_folders(const Message& m)
{
	for (auto f : m.folders)
	{
		f->addMsg(this);
	}
}

void Message::remove_from_folders()
{
	for (auto f : folders)
	{
		f->remMsg(this);
	}
}


Message::Message(const Message& m) : context(m.context), folders(m.folders)
{
	add_to_folders(m);
}


Message& Message::operator=(const Message& rhs)
{
	remove_from_folders();
	context = rhs.context;
	folders = rhs.folders;
	add_to_folders(rhs);
	return *this;
}


Message::~Message()
{
	remove_from_folders();
}

void Message::swap(Message& lhs, Message& rhs)
{
	using std::swap;
	for(auto f : lhs.folders)
		f->remMsg(&lhs);
	for (auto f : rhs.folders)
		f->remMsg(&rhs);

	std::swap(lhs.context, rhs.context);
	std::swap(lhs.folders, rhs.folders);

	for (auto f : lhs.folders)
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);
}

void Message::print_debug()
{
	std::cout << context << std::endl;
}

/*--------------------- Message Class End---------------------*/


/*---------------------- Folder Class ----------------------*/
class Folder
{
	friend class Message;
	friend void swap(Message&, Message&);
	friend void swap(Folder&, Folder&);
public:
	explicit Folder(const std::string& str = "") : name(str) {}
	Folder(const Folder&);
	Folder& operator=(const Folder&);
	~Folder();

	void addMsg(Message* m)
	{
		messages.insert(m);
	}
	void remMsg(Message* m)
	{
		messages.erase(m);
	}

	void print_debug();



private:
	std::string name;
	std::set<Message*> messages;

	void add_to_messages(const Folder& f)
	{
		for (auto m : f.messages)
		{
			m->addFldr(this);
		}
	}

	void remove_from_messages()
	{
		for (auto m : messages)
		{
			m->remFlddr(this);
		}
	}
};

Folder::Folder(const Folder& f) : name(f.name), messages(f.messages)
{
	add_to_messages(f);
}

Folder& Folder::operator=(const Folder& rhs)
{
	remove_from_messages();
	name = rhs.name;
	messages = rhs.messages;
	add_to_messages(rhs);
	return *this;
}

Folder::~Folder()
{
	remove_from_messages();
}


void swap(Folder& lhs, Folder& rhs)
{
	using std::swap;
	for (auto m : lhs.messages)
		m->remFlddr(&lhs);
	for (auto m : rhs.messages)
		m->remFlddr(&rhs);

	std::swap(lhs.name, rhs.name);
	std::swap(lhs.messages, rhs.messages);

	for (auto m : lhs.messages)
		m->addFldr(&lhs);
	for (auto m : rhs.messages)
		m->addFldr(&rhs);
}

void Folder::print_debug()
{
	for (auto m : messages)
		std::cout << m->context << " ";
	std::cout << std::endl;
}
/*--------------------- Folder Class End---------------------*/

#endif // MESSAGE_FOLDER