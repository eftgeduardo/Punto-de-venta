
#include "MyLists.h"


void List::add(IntrusiveNode* node) {
	//auto node = allocator();
	if (head != nullptr) {
		tail->next = node;
		tail = node;
	}
	else {
		head = node;
		tail = node;
	}
	count++;
	//return node;
}
IntrusiveNode* List::get(int position) {
	auto node = head;
	for (int i = 0; i < position; i++) {
		node = node->next;
	}
	return node;
}
void List::remove(int position) {
	if (position == 0) {
		auto to_delete = head;
		head = to_delete->next;
		if (tail == to_delete) {
			tail = nullptr;
		}
		delete to_delete;
		count--;
		return;
	}
	if (position < count) {
		auto prev = get(position - 1);
		auto to_delete = prev->next;
		auto next = to_delete->next;
		prev->next = next;
		if (tail == to_delete) {
			tail = prev;
		}
		delete to_delete;
	}
	count--;


}
void List::display()
{
	auto* node = head;

	for (int i = 0; i < count; i++) {
		node->display(std::cout);
		//std::cout << *(Product*)node;
		node = node->next;
	}

}
void List::SaveData()
{
	auto* node = head;

	for (int i = 0; i < count; i++) {
		node->SaveData(*head);
		node = node->next;
	}


}



std::ostream& operator<<(std::ostream& os, Product& pd)
{


	std::cout << std::left << std::setw(5) << pd.id << std::left << std::setw(15) << pd.product << std::left << std::setw(5)
		<< pd.pc << std::left << std::setw(5) << pd.pv << std::left << std::setw(15) << pd.existencia
		<< std::left << std::setw(20) << pd.nr;
	if (pd.existencia < pd.nr) {
		std::cout << std::left << std::setw(15) <<"   *";
	}
	else std::cout << std::endl;

	return os;
	// TODO: insert return statement here
}
std::ostream& operator<<(std::ostream& os, Account& acc)
{

	os << std::left << std::setw(15) << acc.account << std::left << std::setw(10) << (acc.isadmin ? "Si" : "No") <<  
		"PV: " <<std::left << std::setw(8) << acc.pv_caja << "PC: " << std::left << std::setw(8) << acc.pc_caja << std::endl;

	return os;
}
std::ostream& operator<<(std::ostream& os, Venta& ven) {
	std::cout << std::left << std::setw(10) << ven.product << std::left << std::setw(10) << ven.cantidad << std::left << std::setw(10)
		<< ven.precioUnitario << std::left << std::setw(10) << ven.precioUnitario * ven.cantidad  << std::endl;
	return os;
}



void PrintInventoryTags() {
	std::cout << std::left << std::setw(5) << "ID" << std::left << std::setw(15) << "producto" << std::left << std::setw(5)
		<< "PC" << std::left << std::setw(5) << "PV" << std::left << std::setw(15) << "Existencias"
		<< std::left << std::setw(20) << "Nivel de reorden" <<  std::left << std::setw(15)<<"resurtir" << std::endl << std::endl;
}

void PrintAccountTags()
{
	std::cout << std::left << std::setw(15) << "cuenta " << std::left << std::setw(10) << "administrador" << std::endl << std::endl;
}


int findProduct(List list, std::string ProductSearched)
{
	//list.count
	IntrusiveNode* pd = new Product();
	pd = list.head;

	for (int position = 0; position < list.count; position++) {
		if (((Product*)pd)->product == ProductSearched)
			return position;
		pd = pd->next;

	}
	return -1;


}
int findProduct(List list, int ID)
{
	//list.count
	IntrusiveNode* pd = new Product();
	pd = list.head;

	for (int position = 0; position < list.count; position++) {
		if (((Product*)pd)->id == ID)
			return position;
		pd = pd->next;

	}
	return -1;


}

int findAccount(List list, std::string account_searched)
{
	//list.count
	IntrusiveNode* pd = new Account();
	pd = list.head;

	for (int position = 0; position < list.count; position++) {
		if (((Account*)pd)->account == account_searched)
			return position;
		pd = pd->next;

	}
	return -1;
}

void DisplayProduct(List list, std::string ProductSearched)
{
	IntrusiveNode* pd = new Product();
	pd = list.head;

	

	for (int position = 0; position < list.count; position++) {
		if (((Product*)pd)->product == ProductSearched) {
			PrintInventoryTags();
			std::cout << *(Product*)pd;
			return;
		}

		pd = pd->next;

	}
	std::cout << "no existe producto"<<std::endl;
}
void DeepCopyProduct(Product* pd, Product* to_copy)
{
	pd->id = to_copy->id;
	pd->existencia = to_copy->existencia;
	pd->nr = to_copy->nr;
	pd->pc = to_copy->pc;
	pd->product = to_copy->product;
	pd->pv = to_copy->pv;
}
void SwapListElements(IntrusiveNode* ActualNode)
{
	IntrusiveNode* NextNode = new Product();
	NextNode = ActualNode->next;
	IntrusiveNode* temp = new Product();

	////actual->temp
	DeepCopyProduct((Product*)temp, (Product*)ActualNode);
	//next->actual 
	DeepCopyProduct((Product*)ActualNode, (Product*)NextNode);
	//temp->next
	DeepCopyProduct((Product*)NextNode, (Product*)temp);

}
void SortProductsAlpha(List list)
{
	IntrusiveNode* TempActual = new Product();


	IntrusiveNode* TempNext = new Product();
	int i = 0;


	for (i = 0; i < list.count - 1; i++) {
		TempActual = list.head;
		TempNext = TempActual->next;
		for (int j = 0; j < list.count - i - 1; j++) {
			if (((Product*)TempNext)->product.compare(((Product*)TempActual)->product) == -1) {//si sale positivo significa que el actual es menor que el siguiente
				//std::cout << "hola" << TempNext->producto.compare(TempActual->producto) << std::endl;
				SwapListElements(TempActual);
			}
			TempActual = TempNext;
			TempNext = TempActual->next;
		}

		//sino huba CAMBIO un break;
	}


}

void SortProductsID(List list)
{
	IntrusiveNode* TempActual = new Product();
	IntrusiveNode* TempNext = new Product();

	for (int i = 0; i < list.count - 1; i++) {
		TempActual = list.head;
		TempNext = TempActual->next;
		for (int j = 0; j < list.count - i - 1; j++) {
			if (((Product*)TempNext)->id<((Product*)TempActual)->id) {//si sale positivo significa que el actual es menor que el siguiente
				//std::cout << "hola" << TempNext->producto.compare(TempActual->producto) << std::endl;
				SwapListElements(TempActual);
			}
			TempActual = TempNext;
			TempNext = TempActual->next;
		}

		//sino huba CAMBIO un break;
	}
}

void EraseToRewrite(std::string Filename)
{

	//std::fstream Data("Lists.bin");
	//std::remove("Lists.bin");
	std::ofstream ofs;
	ofs.open(Filename, std::ofstream::out | std::ofstream::trunc);
	ofs.close();



}
void LoadProductData(std::string filename,List& list)
{	
	int pointer = 0;//position PTR where in archive I am
	std::ifstream file(filename, std::ifstream::binary);
	file.seekg(0, file.end);
	int length = file.tellg();//lenght of archive

	while (pointer != length) {
		int temp_id = 0;
		int temp_pv = 0;
		int temp_existencias = 0;
		int temp_pc = 0;
		int temp_nr = 0;
		std::string temp_product = "";
		char ch;
		char SizeString;

		file.seekg(pointer);
		file.read(&SizeString, sizeof(SizeString));
		for (char i = 0; i < SizeString; i++) {
			file.read(&ch, sizeof(char));
			temp_product.push_back(ch);
		}
		file.read(reinterpret_cast<char*>(&temp_id), sizeof(int));//id
		file.read(reinterpret_cast<char*>(&temp_pv), sizeof(int));//pv

		file.read(reinterpret_cast<char*>(&temp_existencias), sizeof(int));
		file.read(reinterpret_cast<char*>(&temp_pc), sizeof(int));
		file.read(reinterpret_cast<char*>(&temp_nr), sizeof(int));

		list.add(new Product(temp_id, temp_product, temp_pc, temp_pv, temp_existencias, temp_nr));
		pointer = file.tellg();//position in file

	}



	file.close();

}


void LoadAccountData(std::string filename, List& list)
{
	int pointer = 0;//position PTR where in archive I am
	std::ifstream file(filename, std::ifstream::binary);
	file.seekg(0, file.end);
	int length = file.tellg();//lenght of archive

	while (pointer != length) {
		int temp_pc_caja;
		int temp_pv_caja;
		bool temp_isadmin;
		char SizeString_accounts;
		char SizeString_password;
		std::string temp_account="";
		std::string temp_password="";
		char ch;
		file.seekg(pointer);
		file.read(&SizeString_accounts, sizeof(SizeString_accounts));
		pointer = file.tellg();//position in file
		//aqui el read
		for (char i = 0; i < SizeString_accounts; i++) {
			file.read(&ch, sizeof(char));
			temp_account.push_back(ch);
		}
		pointer = file.tellg();//position in file
		file.read(&SizeString_password, sizeof(SizeString_password));
		//aqui el read
		pointer = file.tellg();//position in file
		for (char i = 0; i < SizeString_password; i++) {
			file.read(&ch, sizeof(char));
			temp_password.push_back(ch);
		}
		//todo lo demas
		pointer = file.tellg();//position in file
		file.read(reinterpret_cast<char*>(&temp_isadmin), sizeof(char));
		file.read(reinterpret_cast<char*>(&temp_pc_caja), sizeof(temp_pc_caja));
		file.read(reinterpret_cast<char*>(&temp_pv_caja), sizeof(temp_pv_caja));
		list.add(new Account(temp_account, temp_password, temp_isadmin, temp_pc_caja, temp_pv_caja));

		pointer = file.tellg();//position in file
	}



	file.close();

}

Product::Product(int id, std::string product, int pc, int pv, int existencias, int nr)
{
	this->id = id;
	this->product = product;
	this->pv = pv;
	this->existencia = existencias;
	this->nr = nr;
	this->pc = pc;
}
void Product::display(std::ostream& os)
{
	os << *this;
}
void Product::SaveData(IntrusiveNode& head)
{
	using namespace std::string_literals;
	auto data = *this;

	if (data.next == head.next) {
		EraseToRewrite(Productfilename);

	}
	//auto nombre = ;`
	char SizeString = char(data.product.size());
	std::ofstream file(Productfilename, std::ios_base::app | std::ofstream::binary);
	//"res\\Product.bin"
	//string send

	file.write(&SizeString, sizeof(SizeString));

	file.write(data.product.data(), data.product.size());
	//todo lo demas
	file.write(reinterpret_cast<char*>(&data.id), sizeof(data.id));
	file.write(reinterpret_cast<char*>(&data.pv), sizeof(data.pv));
	file.write(reinterpret_cast<char*>(&data.existencia), sizeof(data.existencia));
	file.write(reinterpret_cast<char*>(&data.pc), sizeof(data.pc));
	file.write(reinterpret_cast<char*>(&data.nr), sizeof(data.nr));

	//Data.write(reinterpret_cast<char*>(&SizeString), sizeof( SizeString));
	file.close();

}


Account::Account(std::string account, std::string password, bool isadmin)
{
	this->account = account;
	this->password = password;
	this->isadmin = isadmin;

}
Account::Account(std::string account, std::string password, bool isadmin, int pc_caja, int pv_caja)
{

	this->account = account;
	this->password = password;
	this->isadmin = isadmin;
	this->pc_caja = pc_caja;
	this->pv_caja = pv_caja;
}
void Account::display(std::ostream& os)
{
	os << *this;
}
void Account::SaveData(IntrusiveNode& head)
{
	auto data = *this;
	if (data.next == head.next) {
		EraseToRewrite(Accountfilename);

	}
	//auto nombre = ;
	//char nombre[5] = "hola";
	char SizeString_accounts = char(data.account.size());
	char SizeString_password = char(data.password.size());
	std::ofstream file(Accountfilename, std::ios_base::app | std::ofstream::binary);
	//"res\\Product.bin"
	//string send
	file.write(&SizeString_accounts, sizeof(SizeString_accounts));
	file.write(data.account.data(), data.account.size());

	file.write(&SizeString_password, sizeof(SizeString_password));
	file.write(data.password.data(), data.password.size());

	//todo lo demas
	file.write(reinterpret_cast<char*>(&data.isadmin), sizeof(char));
	file.write(reinterpret_cast<char*>(&data.pc_caja), sizeof(data.pc_caja));
	file.write(reinterpret_cast<char*>(&data.pv_caja), sizeof(data.pv_caja));
	//Data.write(reinterpret_cast<char*>(&SizeString), sizeof( SizeString));

	file.close();
}

Venta::Venta(std::string product, int number, int precio)
{


	this->product = product;
	this->cantidad = number;
	this->precioUnitario = precio;

}

void Venta::display(std::ostream& os)
{
	os<<*this;
}

void Venta::SaveData(IntrusiveNode& head)
{

	return;
}

void List::EmptyList()
{
	//head

	if (count > 0) {
		IntrusiveNode* node = new Venta();
		node = head;
		
		if (count > 1) {
			IntrusiveNode* Nextnode = new Venta();
			Nextnode = node->next;
			int i = 0;
			for (i = 0; i < count - 1; i++) {

				delete ((Venta*)node);
				node = new Venta();
				//IntrusiveNode* node = Nextnode;
				node = Nextnode;
				Nextnode = node->next;
			}
			//delete ((Venta*)node);
		}
		else {
			delete ((Venta*)node);
		}
		count = 0;
		head=nullptr;

	}



}
