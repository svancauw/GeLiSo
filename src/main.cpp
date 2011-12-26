#include "channel/channel.hh"
#include "translator/translator.hh"

/*int main()
{
	using namespace GeLiSo;
	using namespace std;
	using namespace boost::uuids;
	
	//(1) create a channel and a variable map
	channel ch("127.0.0.1", 2222, 3333);
	variableMap varmap;
	
	//(2) loop : receive messages, behave accordingly and answer
	while(1)
	{
		//the new message received
		string newMessage = ch.receive();
		
		//acknowledgment (a UUID if we create a new variable)
		string ack = applyMessage(varmap, newMessage);
				
		//we send the ack
		ch.send(ack);
		
		//(3) if we received the message "beginSearch" message , begin the search
		if(!strcmp(ack.c_str(), "Quit"))
			break;
	}
	
	
	return 0;
	
}*/


#include "GeLiSo/geliso.hh"
int main()
{
	//test main
	using namespace GeLiSo;
	using namespace std;
	using namespace boost::uuids;
	using namespace MPG;
	
	GeLiSoSpace sp;
	GRelation glb1(3);
	GRelation lub1(3);
	
	GRelation glb2(3);
	GRelation lub2(3);
	
	GRelation glb3(3);
	GRelation lub3(3);
	
	int myints[] = {1,2,3};
	int myints2[] = {6,7,8};
	vector<int> comps1 (myints, myints + sizeof(myints) / sizeof(int) );
	vector<int> comps2 (myints2, myints2 + sizeof(myints2) / sizeof(int) );

	Tuple t11(comps1);
	Tuple t12(comps2);
	
	Tuple t21(comps1);
	Tuple t22(comps2);
	
	Tuple t31(comps1);
	Tuple t32(comps2);
	
	lub1.add(t11);
	lub1.add(t12);
	
	lub2.add(t21);
	lub2.add(t22);
	
	lub3.add(t31);
	lub3.add(t32);
	
	GeLiSoCPRelVar& var1 = sp.newCPRelVar(glb1,lub1);
	GeLiSoCPRelVar& var2 = sp.newCPRelVar(glb2,lub2);
	/*GeLiSoCPRelVar& var3 = sp.newCPRelVar(glb3,lub3);*/
	
	cout << "indexes in main : " << var1.getVectorIndex() << var2.getVectorIndex() << endl;
	
	sp.debug();	

	//ERROR : Assertion failed: (px != 0), function operator->, file /usr/local/include/boost/smart_ptr/shared_ptr.hpp, line 424.
	//Seems that there is a null pointer exception ...
	
	//error only if we print the space before posting the constraint !!!
	intersect(sp,var1,var2,var1);
	
	sp.debug();
	
	
	
	
	//sp.debug();
	
	
}

/*int main()
{
	//test main
	using namespace GeLiSo;
	using namespace std;
	using namespace boost::uuids;
	using namespace MPG;
	
	GeLiSoSpace sp;
	GRelation glb1(5);
	GRelation lub1(5);
	
	GRelation glb2(5);
	GRelation lub2(5);
	
	GRelation glb3(5);
	GRelation lub3(5);
	
	int myints[] = {1,2,3,4,5};
	int myints2[] = {6,7,8,9,10};
	vector<int> comps1 (myints, myints + sizeof(myints) / sizeof(int) );
	vector<int> comps2 (myints2, myints2 + sizeof(myints2) / sizeof(int) );

	Tuple t11(comps1);
	Tuple t12(comps2);
	
	Tuple t21(comps1);
	Tuple t22(comps2);
	
	Tuple t31(comps1);
	Tuple t32(comps2);
	
	lub1.add(t11);
	lub1.add(t12);
	
	lub2.add(t21);
	lub2.add(t22);
	
	lub3.add(t31);
	lub3.add(t32);
	
	GeLiSoCPRelVar& var1 = sp.newCPRelVar(glb1,lub1);
	GeLiSoCPRelVar& var2 = sp.newCPRelVar(glb2,lub2);
	/*GeLiSoCPRelVar& var3 = sp.newCPRelVar(glb3,lub3);
	
	cout << "indexes in main : " << var1.getVectorIndex() << var2.getVectorIndex() << endl;
	
	sp.debug();	

	//ERROR : Assertion failed: (px != 0), function operator->, file /usr/local/include/boost/smart_ptr/shared_ptr.hpp, line 424.
	//Seems that there is a null pointer exception ...
	
	//error only if we print the space before posting the constraint !!!
	intersect(sp,var1,var2,var1);
	
	sp.debug();
	
	
	
	
	//sp.debug();
	
	
}*/

