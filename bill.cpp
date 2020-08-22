 //Program for creating bill in a supermarket.
 #include<iostream.h>   //Header file for input and output
 #include<conio.h>      //Header file  for getch(),clrscr() and gotoxy
 #include<fstream.h>    //Header file for file
 #include<stdio.h>      //Header file for gets(),rename() and remove()
 #include<process.h>    //Header file for exit()


 int flag=0;  // global declaration of variables

 struct date
 {
  int mm,dd,yy;
 };


 class item
 {
  int itemno;
  date d;
  float stockqty;
  public:
  void adddata();
  void showdata();
  void report();
  void modstock(int);
  int retno()
  {
   return (itemno);
  }
 };
 void item::adddata()  //function definition
 {
  cout<<"\n\n\tItem No: ";
  cin>>itemno;
  cout<<"\n\n\tQuantity:";
  cin>>stockqty;
  cout<<"\n\n\tManufacturing Date(dd-mm-yy): ";
  cin>>d.mm>>d.dd>>d.yy;
 }
 void item::showdata()
 {
  cout<<"\n\n\tItem No: ";
  cout<<itemno;
  cout<<"\n\n\tQuantity:";
  cout<<stockqty;
  cout<<"\n\n\tManufacturing Date(dd-mm-yy): ";
  cout<<d.mm<<"-"<<d.dd<<"-"<<d.yy;
 }
 void item::report()
 {
  cout<<"\n\t "<<itemno<<"\t "<<stockqty;
 }
 void item::modstock(int qty)
 {
  stockqty-=qty;
 }

 class itemdetails:public item
 {
  char name[25];
  float price,tax,dis,netamt,gross;
  int quantity;
  public:
  void add();
  void show();
  void reportbill();
  void reportstock();
  void calculate(int);
  float retnetamt()
  {
   return(netamt);
  }
  void retqty(int qty)
  {
   quantity=qty;
  }
 };
 void itemdetails::add()
 {
  item::adddata();
  cout<<"\n\n\tName of the item:";
  gets(name);
  cout<<"\n\n\tPrice:";
  cin>>price;
  cout<<"\n\n\tTax percent:";
  cin>>tax;
  cout<<"\n\n\tDiscount percent:";
  cin>>dis;
 }

 void itemdetails::calculate(int qty)
 {
  gross=price+(price*(tax/100));
  netamt=qty*(gross-(gross*(dis/100)));
 }
 void itemdetails::show()
 {
  item::showdata();
  cout<<"\n\n\tName of the item:";
  cout<<name;
  cout<<"\n\n\n\t\t*********************************************";
  cout<<"\n\t\t          DETAILS          ";
  cout<<"\n\t\t*********************************************";
  cout<<"\n\n\t\tPRICE           :"<<price;
  cout<<"\n\n\t\tTAX PERCENTAGE           :"<<tax;
  cout<<"\n\n\t\tDISOUNT PERCENTAGE           :"<<dis;
  cout<<"\n\t\t*********************************************";
 }
 void itemdetails::reportbill()
 {
  cout<<"\t"<<name<<"\t "<<price<<"\t "<<quantity<<"     \t\t"<<tax<<"\t   "<<dis<<"\t          "<<netamt<<endl;
 }
 void itemdetails::reportstock()
 {
  item::report();
  cout<<"\t\t"<<name<<"\t\t"<<price;
 }


 void main()
 {
  clrscr(); // clears the output screen
  int cho,ch,f,op,no,ino,x;
  char ans,o;
  itemdetails obj;
  float total;
  int qty;
  do
  {
   clrscr();
   cout<<"\n\n\n\t\t\tSUPERMARKET BILLING SYSTEM\n\n";
   cout<<"\t\t==========================================";
   cout<<"\n\n\t\t1.ADMINISTRATOR -DETAILS OF STOCK\n\n";
   cout<<"\t\t2.BILLLING\n\n";
   cout<<"\t\t3.EXIT\n\n";
   cout<<"\t\tPlease enter the required option:";
   cin>>cho;
   switch(cho)
   {

	    case 1:do
		   {
		    clrscr();
		    cout<<"\n\n\n\t\t\tSUPER MARKET - STOCK DETAILS\n\n"; //main menu
		    cout<<"\t\t============================================";
		    cout<<"\n\n\t\t1.ADD/REMOVE/EDIT ITEM\n\n";
		    cout<<"\t\t2.SHOW AN ITEM'S DETAILS\n\n";
		    cout<<"\t\t3.STOCK REPORT\n\n";
		    cout<<"\t\t4.BACK TO MAIN MENU\n\n";
		    cout<<"\t\tPlease Enter The Required Option:";
		    cin>>ch;
		    switch(ch)
		    {
			      case 1:do
				     {
				      clrscr();
				      cout<<"\n\n\n\t\t\tStocks Editor\n\n"; //sub menu
				      cout<<"\t\t===========================";
				      cout<<"\n\n\t\t1.Add Item Details\n\n";
				      cout<<"\t\t2.Edit Item Details\n\n";
				      cout<<"\t\t3.Delete Item Details\n\n";
				      cout<<"\t\t4.Back to menu\n\n";
				      cout<<"\t\tPlease Enter The Required Option:";
				      cin>>no;
				      switch(no)
				      {
						 case 1:ofstream fout("stockdetails.dat",ios::app|ios::binary);
							if(!fout)
							cout<<"File cannot be opened for writing";
							else
							{
							 obj.add();
							 fout.write((char*)&obj,sizeof(obj));
							 cout<<"Item successfully added to stock";
							}
							fout.close();
							getch();
							break;

						 case 2:flag=0;
							cout<<"\n\nEnter Item Number to be Edited:";
							cin>>ino;
							ifstream fin("stockdetails.dat",ios::binary);
							ofstream fout1("temp.dat",ios::binary);
							if(!fin)
							 cout<<"\nFile cannot be opened ";
							if(!fout1)
							 cout<<"\nFile cannot be opened ";
							fin.read((char*)&obj,sizeof(obj));
							while(fin)
							{
							 x=obj.retno();
							 if(x==ino)
							 {
							   cout<<endl;
							   cout<<"PRESENT RECORD IS:\n";
							   obj.show();
							   cout<<endl;
							   cout<<"Do you want to modify?(Y/N)\n";
							   cin>>o;
							   if((o=='y')||(o=='Y'))
							   {
							    cout<<"ENTER NEW RECORD:\n";
							    obj.add();
							    fout1.write((char*)&obj,sizeof(obj));
							    flag=1;
							   }
							   else
							    fout1.write((char*)&obj,sizeof(obj));
							 }
							 else
							  fout1.write((char*)&obj,sizeof(obj));
							 fin.read((char*)&obj,sizeof(obj));
							}
							fout1.close();
							fin.close();
							if(flag==1)
							 cout<<"STOCK ITEM MODIFIED\n";
							else
							 cout<<"STOCK ITEM NOT FOUND OR MODIFIED\n";
							remove("stockdetails.dat");
							rename("temp.dat","stockdetails.dat");
							getch();
							break;

						 case 3:flag=0;
							cout<<"Enter item Number to be deleted:";
							cin>>ino;
							cout<<endl;
							ifstream fin1("stockdetails.dat",ios::binary);
							ofstream fout2("temp.dat",ios::binary);
							if(!fin1)
							 cout<<"\nFile cannot be opened ";
							if(!fout2)
							 cout<<"\nFile cannot be opened ";
							fin1.read((char*)&obj,sizeof(obj));
							while(fin1)
							{
							  x=obj.retno();
							  if(x==ino)
							  {
							   cout<<endl<<"DETAILS OF RECORD TO BE DELETED IS:\n\n";
							   obj.show();
							   flag=1;
							  }
							  else
							   fout2.write((char*)&obj,sizeof(obj));
							  fin1.read((char*)&obj,sizeof(obj));
							}
							fout2.close();
							fin1.close();
							if(flag==1)
							 cout<<endl<<"\n\n\t\tSTOCK ITEM DELETED\n\n";
							else
							 cout<<"\t\tSTOCK ITEM NOT FOUND\n";
							remove("stockdetails.dat");
							rename("temp.dat","stockdetails.dat");
							getch();
							break;

						 case 4:break;

						 default:cout<<"\n\n\t\tInvalid Choice";
							 getch();
				      }
				     }while(no!=4);
				     break;

			      case 2:clrscr();
				     flag=0;
				     cout<<"Enter Item Number:";
				     cin>>ino;
				     ifstream fin2("stockdetails.dat",ios::binary);
				     if(!fin2)
				     {
				      cout<<"File cannot be opened";
				      break;
				     }
				     fin2.seekg(0);
				     fin2.read((char*)&obj,sizeof(obj));
				     while(fin2)
				     {
				      x=obj.retno();
				      if(x==ino)
				      {
				       obj.show();
				       flag=1;
				       break;
				      }
				      fin2.read((char*)&obj,sizeof(obj));
				     }
				     if(flag==0)
				      cout<<"Record not found";
				     getch();
				     fin2.close();
				     break;

			      case 3:do
				     {
				      clrscr();
				      cout<<"\n\n\t\t\tStock Report\n"; //sub menu
				      cout<<"\n\t\t===========================";
				      cout<<"\n\n\t\t1.All items\n\n";
				      cout<<"\t\t2.Back to menu\n\n";
				      cout<<"\t\tPlease Enter The Required Option:";
				      cin>>op;
				      if(op==1)
				      {
				       clrscr();
				       cout<<"\n\n\t\t\tSTOCKS DETAILS";
				       cout<<"\n\t\t===============================";
				       cout<<"\n\n\tITEMNO\tQUANTITY\tNAME\t\t\tPRICE\t"<<endl;
				       ifstream fin3("stockdetails.dat",ios::binary);
				       if(!fin3)
				       {
					cout<<"\nFile cannot be opened for reading";
				       }
				       fin3.seekg(0);
				       fin3.read((char*)&obj,sizeof(obj));
				       while(fin3)
				       {
					obj.reportstock();
					fin3.read((char*)&obj,sizeof(obj));
				       }
				       fin3.close();
				       getch();
				      }
				      if(op==2)
				       break;
				     }while(op!=2);
				     break;

			      case 4:break;

			      default:cout<<"Invalid choice";
				      getch();
		    }
		   }while(ch!=4);
		   break;

	    case 2:do
		   {
		    clrscr();
		    cout<<"\n\n\n\t\t\tBILLING\n\n";
		    cout<<"\t\t======================";
		    cout<<"\n\n\t\t1.ADD ITEMS\n\n";
		    cout<<"\t\t2.PRINT BILL\n\n";
		    cout<<"\t\t3.BACK TO MAIN MENU\n\n";
		    cout<<"\t\tPlease enter the required option:";
		    cin>>op;
		    if(op==1)
		    {
		     cout<<"\n\nEnter item number:";
		     cin>>ino;
		     ifstream fin4("stockdetails.dat",ios::binary);
		     ofstream fout3("billreport.dat",ios::app|ios::binary);
		     if(!fin4)
		      cout<<"File cannot be opened for reading";
		     if(!fout3)
		      cout<<"File cannot be opened for writing";
		     fin4.read((char*)&obj,sizeof(obj));
		     while(fin4)
		     {
		      x=obj.retno();
		      if(x==ino)
		      {
		       cout<<"Enter the quantity:";
		       cin>>qty;
		       obj.retqty(qty);
		       obj.calculate(qty);
		       fout3.write((char*)&obj,sizeof(obj));
		       }
		       fin4.read((char*)&obj,sizeof(obj));
		     }
		     fout3.close();
		     fin4.close();
		     ifstream fin5("stockdetails.dat",ios::binary);
		     ofstream fout4("temp.dat",ios::binary);
		     if(!fin5)
		     cout<<"\nFile cannot be opened ";
		     if(!fout4)
		     cout<<"\nFile cannot be opened ";
		     fin5.read((char*)&obj,sizeof(obj));
		     while(fin5)
		     {
		      x=obj.retno();
		      if(x==ino)
		      {
		       obj.modstock(qty);
		       fout4.write((char*)&obj,sizeof(obj));
		      }
		      else
		       fout4.write((char*)&obj,sizeof(obj));
		      fin5.read((char*)&obj,sizeof(obj));
		     }
		     fout4.close();
		     fin5.close();
		     remove("stockdetails.dat");
		     rename("temp.dat","stockdetails.dat");
		     getch();
		    }
		    if(op==2)
		    {
		     clrscr();
		     cout<<"\n\n\t\t\tBILL DETAILS";
		     cout<<"\n\t\t===========================";
		     cout<<"\n\n\tNAME\tPRICE\tquantity\tTAX%\tDISCOUNT%\tNET AMOUNT"<<endl;
		     ifstream fin6("billreport.dat",ios::binary);
		     if(!fin6)
		     {
		      cout<<"\nFile cannot be opened for reading";
		     }
		     total=0;
		     fin6.seekg(0);
		     fin6.read((char*)&obj,sizeof(obj));
		     while(fin6)
		     {
		      if(fin6.eof())
		      break;
		      else
		       {
			obj.reportbill();
			total+=obj.retnetamt();
			f=0;
		       }
		      if(f!=0)
		      total=0;
		      fin6.read((char*)&obj,sizeof(obj)); //reads from the file
		     }
		      cout<<"\n\n\n\t\t\tGrand Total="<<total;
		      getch();
		      fin6.close();
		      fstream fout5("temp.dat",ios::binary);
		      clrscr();
		      cout<<"\n\n\tDo you want to delete the present bill report?";
		      cin>>ans;
		      if((ans=='y')||(ans=='Y'))
		      {
		       remove("billreport.dat");
		       rename("temp.dat","billreport.dat");
		      }
		    }
		    if (op==3)
		     break;
		   }while(op!=3);
		   break;


	    case 3:clrscr();
		   cout<<"\n\n\t\tAre you sure you want to exit?(Y/N)"<<endl;
		   cin>>ans;
		   if((ans=='Y')||(ans=='y'))
		   {
		    clrscr();
		    gotoxy(8,5);  //positions cursor in text window
		    cout<<"PROGRAM BY:";
		    gotoxy(10,8);
		    cout<<"SUZANA ISAAC";
		    getch();
		    exit(0);
		   }
		   else
		    break;

	    default:cout<<"\n\n\t\tInvalid Choice";
		    break;

   }
  }while(cho!=3);
  getch();  // freezes the output screen
 }
