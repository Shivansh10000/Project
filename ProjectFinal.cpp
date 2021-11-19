#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

template <typename V>
class MapNode {
	public:
		string key;
		V value;
		MapNode* next;

		MapNode(string key, V value) {
			this->key = key;
			this->value = value;
			next = NULL;
		}

		~MapNode() {
			delete next;
		}
};

template <typename V>
class ourmap {
	MapNode<V>** buckets;
	int count;
	int numBuckets;

	public:
	ourmap() {
		count = 0;
		numBuckets = 5;
		buckets = new MapNode<V>*[numBuckets];
		for (int i = 0; i < numBuckets; i++) {
			buckets[i] = NULL;
		}
	}

	~ourmap() {
		for (int i = 0; i < numBuckets; i++) {
			delete buckets[i];
		}
		delete [] buckets;
	}

	int size() {
		return count;
	}

	V getValue(string key) {
		int bucketIndex = getBucketIndex(key);
		MapNode<V>* head = buckets[bucketIndex];
		while (head != NULL) {
			if (head->key == key) {
				return head->value;
			}
			head = head->next;
		}
		return 0;
	}

	private:
	int getBucketIndex(string key) {
		int hashCode = 0;

		int currentCoeff = 1;
		for (int i = key.length() - 1; i >= 0; i--) {
			hashCode += key[i] * currentCoeff;
			hashCode = hashCode % numBuckets;
			currentCoeff *= 37;
			currentCoeff = currentCoeff % numBuckets;
		}

		return hashCode % numBuckets;
	}

	public:
	void insert(string key, V value) {
		int bucketIndex = getBucketIndex(key);
		MapNode<V>* head = buckets[bucketIndex];
		while (head != NULL) {
			if (head->key == key) {
				head->value = value;
				return;
			}
			head = head->next;
		}
		head = buckets[bucketIndex];
		MapNode<V>* node = new MapNode<V>(key, value);
		node->next = head;
		buckets[bucketIndex] = node;
		count++;
	}

	V remove(string key) {
		int bucketIndex = getBucketIndex(key);
		MapNode<V>* head = buckets[bucketIndex];
		MapNode<V>* prev = NULL;
		while (head != NULL) {
			if (head->key == key) {
				if (prev == NULL) {
					buckets[bucketIndex] = head->next;
				} else {
					prev->next = head->next;
				}
				V value = head->value;
				head->next = NULL;
				delete head;
				count--;
				return value;
			}
			prev = head;
			head = head->next;
		}
		return 0;
	}

};

class queue {
	string *data;
	int front;
	int rear;
	int size;
	int capacity;
	public :
		queue()
		{
			size = 0;
			front = 0;
			rear = 0;
			data = new string[1000]; 
		}
		void enqueue(string element)
		{
			data[rear] = element;
			rear++;
			size++;
			return;
		}
		string* returnQueue()
		{
			return data;
		}
		int returnsize()
		{
			return size;
		}
		~queue()
		{
			delete [] data;
		}
};

class applicant {
	public :	
		string name1;
		int age1;
		int exp1;
		string qual;
};

class college {
	protected :
		string name;
		string rollno;
		int age;
		int dob;
		int contact;
		public :
			int showScreen()
			{
				int choice = 0;
				do
				{
					if(choice > 5)
					{
						cout<<"\n\n\t\tInvalid Choice !\n\t\t";
						system("pause");
						system("cls");
					}
				system("color E1");
				cout<<"\n\n\t\t\t\t\t\t\tWELCOME TO COLLEGE MANAGEMENT \n\n"; //6 \t were used for centralization
				cout<<"\n\n\t\tLOGIN AS : \n";
				cout<<"\n\n\t\t1. Admin";
				cout<<"\n\n\t\t2. Teacher";
				cout<<"\n\n\t\t3. Student";
				cout<<"\n\n\t\t4. Apply for teacher";
				cout<<"\n\n\t\t5. Exit System";
				cout<<"\n\n\t\t Enter your choice : ";
				cin>>choice;
				}while(choice > 5);
				return choice;
			}
};

class admin : protected college {
	private :
		string stream, rno;
		int rank;
		string qualification;
	public :
		void teacherApplication()
		{
			applicant a;
			cout<<"\n\n\t\t\t\t\t\tAPPLICATION FOR TEACHER\n";
			cout<<"\n\n\t\tApplicant's name : ";
			cin>>a.name1;
			cout<<"\n\n\t\tApplicant's age : ";
			cin>>a.age1;
			cout<<"\n\n\t\tApplicant's experience (in years): ";
			cin>>a.exp1;
			cout<<"\n\n\t\tApplicant's qualification(has to be q1) : "; //qualification has to be q1 for applying
			cin>>a.qual;
			if(a.exp1 < 5)
			{
				cout<<"\n\n\t\tYou dont have enough experience to apply for this job";
				return;
			}
			if(a.age1 < 20)
			{
				cout<<"\n\n\t\tYou have to be more than 20 years old to apply";
				return;
			}
			if(a.age1 > 60)
			{
				cout<<"\n\n\t\tYou cannot apply for this job if you are older than 60 years";
				return;
			}
			if(a.qual != "q1")
			{
				cout<<"\n\n\t\tYour qualification has to be q1 to apply for this job";
				return;
			}
			queue q;
			q.enqueue(a.name1);
			ofstream fout("applications.txt", ios::app);
			fout<<a.name1<<"\t"<<a.age1<<"\t"<<a.exp1<<"\t"<<a.qual<<endl;
			ofstream fout1("line.txt", ios::app);
			string* s = q.returnQueue();
			int total = q.returnsize();
			for(int i=0; i<total; i++)
			{
				fout1<<s[i]<<endl;
			}
			cout<<"\n\n\t\tYou have successfully applied for this job";
			cout<<"\n\n\t\tPlease check your name on the list of applicants";
			ifstream fin("applications.txt", ios::in);
			string qualification;
			int exp;
			fin>>name>>age>>exp>>qualification;
			cout<<"\n\nNAME\tAGE\tEXP\tQUALIFICATION\n";
			while (!fin.eof())
			{
				cout<<name<<"\t"<<age<<"\t"<<exp<<"\t"<<qualification;
				cout<<endl;
				fin>>name>>age>>exp>>qualification;
			}
			
		}
		int adminScreen()
		{
			int choice = 0;
			cout<<"\n\n\t\t\t\t\t\t\tADMIN  \n\n";
			cout<<"\n\n\t\tSELECT THE ACTION YOU WOULD LIKE TO PERFORM : \n\n";
			cout<<"\n\n\t\t1. Add a student(based on rank)\n";
			cout<<"\n\n\t\t2. Add a teacher \n";
			cout<<"\n\n\t\t3. Check Student list\n";
			cout<<"\n\n\t\t4. Check Teacher list\n";
			cout<<"\n\n\t\t Enter your choice : ";
			cin>>choice;
			return choice;
		}
		void addStudent()
		{
			char ch;
			do
			{
				system("cls");
				srand(time(0));
				bool isEligible = true; 
				cout<<"\n\n\t\t\t\t\t\tADD A STUDENT  \n\n\n";
				cout<<"\n\n\t\tStudent's name : ";
				cin>>name;
				cout<<"\n\n\n\t\tStudent's age : ";
				cin>>age;
				cout<<"\n\n\n\t\tStudent's date of birth (ddmmyyyy): ";
				cin>>dob;
				cout<<"\n\n\n\t\tStudent's contact (8 digits): ";
				cin>>contact;
				cout<<"\n\n\n\t\tStudent's rank : ";
				cin>>rank;
				if(rank < 10000) { stream = "COE"; rno = "COE/";
				}
				else if(rank < 13000) { stream = "IT"; rno = "IT/";
				}
				else if(rank < 15000) { stream = "SE"; rno = "SE/";
				}
				else if(rank < 18000) { stream = "MAC"; rno = "MAC/";
				}
				else if(rank <21000) { stream = "ECE"; rno = "ECE/";
				}
				else if(rank < 25000) { stream = "ME"; rno = "ME/";
				}
				else {
				cout<<"\n\n\t\tGiven student is not eligible for admission  hence no record can be added ";
				isEligible = false;
				}
				if(isEligible == true)
				{
					char xy = 'a';
					int random;
					for(int i=0; i<5; i++)
					{
						random = 1 + rand()%10;
						xy += random;
						rno = rno + xy;
					}
					ofstream fout("studentRec.txt", ios::app);
					fout<<"\n"<<name<<"\t"<<rno<<"\t"<<age<<"\t"<<stream<<"\t"<<dob<<"\t"
					<<contact<<"\t"<<rank<<"\n";
					cout<<"\n\n\t\tThe Student's record was added successfully ! ";
					fout.close();
				}
				cout<<"\n\n\t\tDo you want to add another record ?(y/n) ";
				cin>>ch;
			}while(ch == 'y');
			cout<<"\n\n\t\t";
			system("pause");
		}
		void checkstudents()
		{
			cout<<"\n\n\t\t\t\t\t\t\tSTUDENT'S LIST  \n\n\n";
			ifstream fin("studentRec.txt", ios::in);
			if(!fin)
			{
				cout<<"\n\n\t\tFile doesnt exist !";
				return;
			}
			else
			{
				cout<<"NAME"<<"\t"<<"ROLL NO"<<"\t\t"<<"AGE"<<"\t"<<"STREAM"<<"\t"
				<<"DOB"<<"\t\t"<<"CONTACT NO"<<"\t"<<"RANK\n\n\n";
				fin>>name>>rno>>age>>stream>>dob>>contact>>rank;
				while (!fin.eof())
				{
					cout<<name<<"\t"<<rno<<"\t"<<age<<"\t"<<stream<<"\t"
					<<dob<<"\t"<<contact<<"\t"<<rank<<"\n";
					cout<<"\n\n";
					fin>>name>>rno>>age>>stream>>dob>>contact>>rank;
				}
				fin.close();
				system("pause");
			}
		}
		void addteacher()
		{
			cout<<"\n\n\t\t\t\t\t\t\tADD A TEACHER  \n\n";
			cout<<"\n\n\t\tTeacher's name : ";
			cin>>name;
			cout<<"\n\n\n\t\tTeacher's age : ";
			cin>>age;
			cout<<"\n\n\n\t\tTeacher's date of birth (ddmmyyyy): ";
			cin>>dob;
			cout<<"\n\n\n\t\tTeacher's contact : ";
			cin>>contact;
			cout<<"\n\n\n\t\tTeacher's qualification : ";
			cin>>qualification;
			rno = "IT/";
			char xy = 'a';
			int random;
			for(int i=0; i<5; i++)
			{
				random = 1 + rand()%10;
				xy += random;
				rno = rno + xy;
			}
			ofstream fout("teacherRec.txt", ios::app);
			fout<<"\n"<<name<<"\t"<<rno<<"\t"<<age<<"\t"<<dob<<"\t"
				<<contact<<"\t"<<qualification<<"\n";
			cout<<"\n\n\t\tThe Teacher's record was added successfully ! ";
			fout.close();
		}
		void checkteacher()
		{
			cout<<"\n\n\t\t\t\t\t\t\tTEACHER'S LIST  \n\n\n";
			ifstream fin("teacherRec.txt", ios::in);
			if(!fin)
			{
				cout<<"\n\n\t\tFile doesnt exist !";
				return;
			}
			else
			{
				cout<<"NAME"<<"\t\t"<<"ROLL NO"<<"\t\t"<<"AGE"<<"\t"<<"DOB"<<"\t\t"<<"CONTACT"<<"\t  "<<"QUALIFICATION\n\n";
				fin>>name>>rno>>age>>dob>>contact>>qualification;
				while (!fin.eof())
				{
					cout<<name<<"\t\t"<<rno<<"\t"<<age<<"\t"<<dob<<"\t"<<contact<<"\t"<<qualification<<"\n";
					cout<<"\n\n";
					fin>>name>>rno>>age>>dob>>contact>>qualification;
				}
				
			}
			cout<<"\n\n\t\t";
			system("pause");
		}
};

class teacher : protected college{
	int age, dob, contact,phy,chem,math, rank;
	float avg, att;
	string rno, name, qualification, stream;
	int choice = 1;
	public :
		void teacherlogin()
		{
			bool isMember = true;
			string login;
			int password;
			cout<<"\n\n\t\t\t\t\t\tTEACHER'S LOGIN  \n\n\n";
			cout<<"\n\n\t\tLOGIN ID(NAME) : ";
			cin>>login;
			cout<<"\n\n\t\tPASSWORD(DOB) : ";
			cin>>password;
			ifstream fin("teacherRec.txt", ios::in);
			fin>>name>>rno>>age>>dob>>contact>>qualification;
			while (!fin.eof())
			{
				if(login == name && password == dob)
				{
					isMember = true;
					cout<<"\n\n\t\t\t\t\t\t\tWELCOME "<<name<<"\n\n\n";
					cout<<"\n\n\t\tThese are your details according to college record : \n\n";
					cout<<"NAME"<<"\t\t"<<"ROLL NO"<<"\t\t"<<"AGE"<<"\t"<<"DOB"<<"\t\t"<<"CONTACT"<<"\t  "<<"QUALIFICATION\n";
					cout<<name<<"\t\t"<<rno<<"\t"<<age<<"\t"<<dob<<"\t"<<contact<<"\t"<<qualification<<"\n";
					cout<<endl;
					cout<<"\n\t\t";
					system("pause");
					do
					{
						if(choice > 4)
						{
							cout<<"\n\n\t\tINVALID CHOICE !";
						}
						system("cls");
						cout<<"\n\n\t\tWhat would you like to do ? ";
						cout<<"\n\n\t\t1.Add a student's record";
						cout<<"\n\n\t\t2.Schedule a test";
						cout<<"\n\n\t\t3.Check a student's record";
						cout<<"\n\n\t\t4.Exit";
						cout<<"\n\n\t\t Enter your choice : ";
						cin>>choice;
						if(choice == 1)
						{
							bool flag = true;
							system("cls");
							string nameS;
							string namestudent;
							cout<<"\n\n\t\tADD A STUDENT'S RECORD";
							cout<<"\n\n\n\n\t\tEnter the student's name whose record is to be added(must be in college) : ";
							cin>>namestudent;
							ifstream fin("studentRec.txt", ios::in);
							fin>>nameS>>rno>>age>>stream>>dob>>contact>>rank;
							while (!fin.eof())
							{
								if(nameS == namestudent)
								{
									ourmap<int> marks;
									cout<<"\n\n\t\tStudent found ! ";
									flag = true;
									cout<<"\n\n\t\tEnter student's final marks in each subject : ";
									cout<<"\n\n\t\tEnter marks in physics : ";
									cin>>phy;
									marks.insert("physics",phy);
									cout<<"\n\n\t\tEnter marks in chemistry : ";
									cin>>chem;
									marks.insert("chemistry",chem);
									cout<<"\n\n\t\tEnter marks in maths : ";
									cin>>math;
									marks.insert("maths",math);
									avg = (phy + chem + math)/3;
									cout<<"\n\n\t\tThe values of marks for various subjects entered were : ";
									cout<<"\n\n\t\tPhysics : "<<marks.getValue("physics");
									cout<<"\n\n\t\tChemistry : "<<marks.getValue("chemistry");
									cout<<"\n\n\t\tMaths : "<<marks.getValue("maths");
									cout<<"\n\n\t\tEnter the final attendance in % : ";
									cin>>att;
									ofstream fout("teacher.txt", ios::out | ios::app);
									fout<<namestudent<<"\t"<<phy<<"\t"<<chem<<"\t"<<math<<"\t"<<avg<<"\t"<<att<<"\n";
									cout<<"\n\n\t\tThe student record was added successfully !";
									break;
								}
								else
								{
									flag = false;
								}
								fin>>nameS>>rno>>age>>stream>>dob>>contact>>rank;
							}
							if(flag == false)
							{
								cout<<"\n\n\t\tThis is not a student of this collge !";
								cout<<"\n\n\t\tHence no record can be added for this student";
								system("pause");
							}
						}
						else if(choice == 2)
						{
							system("cls");
							string date, subject,mode;
							cout<<"\n\n\n\t\t\t\t\t\t\tSCHEDULE A TEST";
							cout<<"\n\n\n\t\tEnter the date you want to schedule it : (dd/mm/yyyy) : ";
							cin>>date;
							cout<<"\n\n\n\t\tEnter the subject of this test : ";
							cin>>subject;
							cout<<"\n\n\n\t\tEnter the mode of this test (objective/subjective) : ";
							cin>>mode;
							ofstream fout("tests.txt", ios::out | ios::app);
							fout<<date<<"\t"<<subject<<"\t"<<mode<<"\n";
							cout<<"\n\n\t\tThe test was successfully scheduled !";
							system("pause");
							system("cls");
						}
						else if(choice == 3)
						{
							string namestudent, nameS;
							bool checker = true;
							cout<<"\n\n\t\tCHECK A STUDENT'S RECORD";
							cout<<"\n\n\t\tWrite the student's name : ";
							cin>>nameS;
							ifstream fin("teacher.txt", ios::in);
							fin>>namestudent>>phy>>chem>>math>>avg>>att;
							while (!fin.eof())
							{
								if(nameS == namestudent)
								{
									cout<<"\n\n\t\tStudent found ! ";
									cout<<"\n\n\t\tThis student's details are : \n";
									cout<<"NAME\tPHYSICS\tCHEMISTRY\tMATHS\tAVERAGE\tATTENDANCE(%)";
									cout<<endl;
									cout<<namestudent<<"\t"<<phy<<"\t"<<chem<<"\t"<<math
									<<"\t"<<avg<<"\t"<<att;
									cout<<endl;
									checker = true;
									system("pause");
									break;
								}
								else
								{
									checker = false;
								}
								fin>>namestudent>>phy>>chem>>math>>avg>>att;
							}
							if(checker == false)
							{
								cout<<"\n\n\t\tStudent was not found ! ";
							}
						}
					}while(choice != 4);
					break;
				}
				else
				{
					isMember = false;
				}
				fin>>name>>rno>>age>>dob>>contact>>qualification;
				
			}
			if(isMember == false)
			{
				cout<<"\n\n\t\tIncorrect Login ID or password!";
				cout<<"\n\n\t\tPlease enter correct details";
			}
		}
};

class student : protected college{
	string stream;
	int year, rank;
	int gpa;
	float attendance;
	int feedue;
	public :
		void sLogin()
		{
			int choice = 0;
			bool mark = true;
			int key;
			string log;
			cout<<"\n\n\t\t\t\t\t\tSTUDENT'S LOGIN  \n\n\n";
			cout<<"\n\n\t\tLOGIN ID(NAME) : ";
			cin>>log;
			cout<<"\n\n\t\tPASSWORD(DOB) : ";
			cin>>key;
			ifstream fin("studentRec.txt",ios::in);
			fin>>name>>rollno>>age>>stream>>dob>>contact>>rank;
			while(!fin.eof())
			{
				if(name == log && key == dob)
				{
					mark = true;
					cout<<"\n\n\t\t\t\t\t\t\tWELCOME "<<name<<"\n\n\n";
					cout<<"\n\n\t\tThese are your details according to college record : \n\n";
					cout<<"NAME\tROLLNO\t\tAGE\tSTREAM\tDOB\t\tCONTACT\t\tRANK";
					cout<<"\n";
					cout<<name<<"\t"<<rollno<<"\t"<<age<<"\t"<<stream<<"\t"
					<<dob<<"\t"<<contact<<"\t"<<rank;
					cout<<"\n";
					do
					{
						cout<<"\n\n\t\tWhat would you like to do ? ";
						cout<<"\n\n\t\t1.Check your academic record ";
						cout<<"\n\n\t\t2.Check test dates ";
						cout<<"\n\n\t\t3.Exit";
						cout<<"\n\n\t\tEnter your choice : ";
						cin>>choice;
						if(choice == 1)
						{
							string nameS;
							int phy,chem,math,att;
							float avg;
							ifstream fin("teacher.txt",ios::in);
							fin>>nameS>>phy>>chem>>math>>avg>>att;
							while (!fin.eof())
							{
								if(name == nameS)
								{
									cout<<"\n\n\t\tYour academic details are : \n\n\n";
									cout<<"NAME\tPHYSICS\tCHEMISTRY\tMATHS\tAVERAGE\tATTENDANCE(%)";
									cout<<endl;
									cout<<name<<"\t"<<phy<<"\t"<<chem<<"\t\t"<<math
									<<"\t"<<avg<<"\t"<<att;
									cout<<endl;
									system("pause");
									break;
								}
								fin>>nameS>>phy>>chem>>math>>avg>>att;
							}
						}
						else if(choice == 2)
						{
							string date,subject,mode;
							ifstream fin("tests.txt", ios::in);
							fin>>date>>subject>>mode;
							cout<<"\n\n\t\tThe tests scheduled are : \n";
							cout<<"\n\nDATE\t\tSUBJECT\t\tMODE\n\n\n";
							while (!fin.eof())
							{	
								cout<<date<<"\t"<<subject<<"\t\t"<<mode;
								cout<<"\n\n";
								fin>>date>>subject>>mode;
							}
						}
						system("pause");
						system("cls");
					}while(choice != 3);
					break;
				}
				else
				{
					mark = false;
				}
				fin>>name>>rollno>>age>>stream>>dob>>contact>>rank;
			}
			if(mark == false)
			{
				cout<<"\n\n\t\t\t\t\tINVALID USERNAME OR PASSWORD !";
				return;
			}
		}
		
		
};


int main() {
	college c;
	int choice;
	do
	{
		system("cls");
		choice = c.showScreen();
		system("cls");
		if(choice == 1)
		{
			admin a;
			int choice1 = a.adminScreen();
			system("cls");
			if(choice1 == 1)
			{
				a.addStudent();
			}
			else if(choice1 == 2)
			{
				a.addteacher();
			}
			else if(choice1 == 3)
			{
				a.checkstudents();
			}
			else
			{
				a.checkteacher();
			}
		}
		else if(choice == 2)
		{
			teacher t;
			t.teacherlogin();
			system("pause");
		}
		else if(choice == 3)
		{
			student s;
			s.sLogin();
			system("pause");
		}
		else if(choice == 4)
		{
			admin a1;
			a1.teacherApplication();
			system("pause");
		}
	}while(choice != 5);
	return 0;
}
