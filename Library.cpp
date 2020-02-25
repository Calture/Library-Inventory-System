#include<iostream>
#include<fstream>
using namespace std;

class Library
{
	private:
		char name[50];
		char bkname[50];
		int bkno;
		int rollno;
	public:
		void add_student(void);
		void add_book(void);
		void show_student(void);
		void show_book(void);
		int get_rollno(void);
		int get_bkno(void);
		void borrow(void);
		void show_borrow(void);
};

void Library::add_student(void)
{
	cout<<"Enter Name Of Student : ";
	fflush(stdin);
	gets(name);
	cout<<"Enter Roll Number Of Student : ";
	cin>>rollno;
}

void Library::show_student(void)
{
	cout<<"\n		        *	"<<name<<"			"<<rollno<<"	  *";
}

void Library::add_book(void)
{
	cout<<"Enter Name Of The Book : ";
	fflush(stdin);
	gets(bkname);
	cout<<"Enter Book Number : ";
	cin>>bkno;
}

void Library::show_book(void)
{
	cout<<"\n		        *	"<<bkname<<"			"<<bkno<<"	  *";
}

int Library::get_rollno(void)
{
	return rollno;
}

int Library::get_bkno(void)
{
	return bkno;
}

void Library::show_borrow(void)
{
	cout<<"\n		        *	"<<rollno<<"			"<<bkno<<"	  *";
}

void createstudentfile(void)
{
	int num;
	Library obj;
	fstream ofile;
	ofile.open("Student.dat",ios::out|ios::app|ios::binary);
	
	if(!ofile)
	{
		cout<<"ERROR.Cannot Open File.";
		return;
	}
	
	cout<<"How Many Students Do You Wish To Add : ";
	cin>>num;
	
	for(int i=1;i<=num;i++)
	{
		obj.add_student();
		ofile.write((char*)&obj,sizeof(obj));
	}
	ofile.close();
}

void displaystudentfile(void)
{
	Library obj;
	fstream ifile;
	ifile.open("Student.dat",ios::in|ios::binary);
	
	if(!ifile)
	{
		cout<<"ERROR.Cannot Open File.";
		return;
	}
	
	cout<<"\n			***************************************************";
	cout<<"\n			*	Student Name		   Roll Number	  *";
	cout<<"\n			***************************************************";
	
	while(ifile.read((char*)&obj,sizeof(obj)))
	{
		obj.show_student();
	}
	cout<<"\n			***************************************************";

	ifile.close();
}

void createbookfile(void)
{
	int num;
	Library obj;
	fstream ofile;
	ofile.open("Book.dat",ios::out|ios::app|ios::binary);
	
	if(!ofile)
	{
		cout<<"ERROR.Cannot Open File.";
		return;
	}
	
	cout<<"How Many Books Do You Wish To Add : ";
	cin>>num;
	
	for(int i=1;i<=num;i++)
	{
		obj.add_book();
		ofile.write((char*)&obj,sizeof(obj));
	}
	ofile.close();
}

void displaybookfile(void)
{
	Library obj;
	fstream ifile;
	ifile.open("Book.dat",ios::in|ios::binary);
	
	if(!ifile)
	{
		cout<<"ERROR.Cannot Open File.";
		return;
	}
	
	cout<<"\n			***************************************************";
	cout<<"\n			*	Book Name		   Book Number	  *";
	cout<<"\n			***************************************************";
	
	while(ifile.read((char*)&obj,sizeof(obj)))
	{
		obj.show_book();
	}
	cout<<"\n			***************************************************";

	ifile.close();
}

void Library::borrow(void)
{
	int rno,bno;
	int found1=0,found2=0;
	
	cout<<"Enter Roll Number Of Student : ";
	cin>>rno;
	cout<<"Enter Book Number To Be Borrowed : ";
	cin>>bno;
	
	Library obj;
	
	fstream f1;
	f1.open("Student.dat",ios::in|ios::binary);
	fstream f2;
	f2.open("Book.dat",ios::in|ios::binary);
	
	if(!f1)
	{
		cout<<"ERROR.Cannot Open File";
		return;
	}
	if(!f2)
	{
		cout<<"ERROR.Cannnot Open File";
		return;
	}
	
	while(f1.read((char*)&obj,sizeof(obj)))
	{
		if(obj.get_rollno()==rno)
		{
			found1=1;
			break;
		}
	}
	f1.close();
	
	if(found1==0)
		cout<<"\nSorry,Roll Number Does Not Exist.";
	
	while(f2.read((char*)&obj,sizeof(obj)))
	{
		if(obj.get_bkno()==bno)
		{
			found2=1;
			break;
		}
	}
	f2.close();
	
	if(found2==0)
		cout<<"\nSorry,Book Number Does Not Exist.";
	
	if(found1!=0 && found2!=0)
	{
		fstream ofile;
		ofile.open("Borrow.dat",ios::in|ios::app|ios::binary);
		ofile.write((char*)&obj,sizeof(obj));
		ofile.close();	
	}
}

void displayborrowfile(void)
{
	Library obj;
	fstream ifile;
	ifile.open("Borrow.dat",ios::in|ios::binary);
	
	if(!ifile)
	{
		cout<<"ERROR.Cannot Open File.";
		return;
	}
	
	cout<<"\n			***************************************************";
	cout<<"\n			*	Roll Number		   Book Number	  *";
	cout<<"\n			***************************************************";
	
	while(ifile.read((char*)&obj,sizeof(obj)))
	{
		obj.show_borrow();
	}
	cout<<"\n			***************************************************";

	ifile.close();
}
int main()
{
	int choice;
	do
	{
		cout<<"\n1-Add Students";
		cout<<"\n2-Display All Students";
		cout<<"\n3-Add Books";
		cout<<"\n4-Display All Books";
		cout<<"\n5-Borrow A Book";
		cout<<"\n6-View Borrowed Books";
		cout<<"\n7-Exit";
		cout<<"\nEnter Choice : ";
		cin>>choice;
		
		switch(choice)
		{
			case 1:createstudentfile();break;
			case 2:displaystudentfile();break;
			case 3:createbookfile();break;
			case 4:displaybookfile();break;
			case 5:
			{
				Library ob;
				ob.borrow();
				break;
			}
			case 6:displayborrowfile();break;
			case 7:break;
			default:cout<<"Wrong Input";
		};
	}while(choice!=7);
	return 0;
}
