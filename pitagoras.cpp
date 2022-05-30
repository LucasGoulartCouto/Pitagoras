#include <iostream>
using std::cout;
using std::cin;
using std::boolalpha; // exibe valores bool como true e false

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <utility>
using std::pair;

#include <iterator>
using std::iterator;

typedef struct{
    string cod_cliente;
    string nome;
    bool ativo;

    void print(){
        cout << boolalpha;
        cout << "{" << cod_cliente << ", " << nome << ", " << ativo << "}" << '\n';
    }

    void ativar(){
        ativo = true;
    }

    void inativar(){
        ativo = false;
    }
}Cliente;

typedef struct{
    string codigo;
    string nome;
    double preco;
    string data;

    void print(){
        cout << "{" << codigo << ", " << nome << ", " << preco << ", ";
        cout << data << "}" << '\n';
    }
}Combustivel;


typedef struct{
    string data;
    string cod_cliente;
    string cod_produto;
    double quantidade;
    double valor_do_litro;
    double total;
    string responsavel;
    bool pago;

    void print(){
        cout << boolalpha;        
        cout << "{" << data << ", " << cod_cliente << ", " << cod_produto << ", ";
        cout << quantidade << ", " << valor_do_litro << ", " << total << ", ";
        cout << responsavel << ", " << pago << "}\n";   
    }
} Venda;


void init(map<string,Cliente>& m, map<string,Combustivel>& c){
    m.insert(pair<string, Cliente>("101", {"101", "Jose da Silva", true}));
    m.insert(pair<string, Cliente>("102", {"102", "Marcos Cardoso", true}));
    m.insert(pair<string, Cliente>("103", {"103", "Keyla Pedroso", true}));
    m.insert(pair<string, Cliente>("104", {"104", "Demerval Zoroastro", false}));
    m.insert(pair<string, Cliente>("105", {"105", "William J. dos Santos", true}));
    m.insert(pair<string, Cliente>("106", {"106", "Regina Marcolino Ferreira", false}));
    m.insert(pair<string, Cliente>("107", {"107", "Tiago Wesley de Oliveira", true}));

    c.insert(pair<string, Combustivel>("D01", {"D01 ", "S10", 6.5, "10/05/2022"}));
    c.insert(pair<string, Combustivel>("G05", {"G05 ", "Gasolina", 8.5, "15/05/2022"}));
    c.insert(pair<string, Combustivel>("E07", {"E07 ", "Etanol", 7.5, "20/05/2022"}));
}

int menu(){
    cout << '\n';
    cout << "================================\n";
    cout << "<< 1 >> Venda\n";
    cout << "<< 2 >> Listar pedidos em aberto\n";
    cout << "<< 3 >> Listar todos os pedidos\n";
    cout << "<< 4 >> Listar clientes\n";
    cout << "<< 5 >> Listar combustiveis\n";
    cout << "<< 6 >> Cadastrar cliente\n";
    cout << "<< 7 >> Ativar/Desativar cliente\n";
    cout << "<< 0 >> Sair\n";
    cout << "================================\n";
    cout << "Entre com sua opcao: ";
    int op;
    cin >> op;    
    cin.ignore(256, '\n'); // limpar o buffer de entrada
    while(op < 0 || op > 7 || !cin.good()){
        cin.clear();// limpar buffer de entrada
        cin.ignore(256, '\n');
        cout << "\n>>> Opcao invalida <<< \n\n";
        cout << "Entre com sua opcao: ";
        cin >> op;
        cin.ignore(256, '\n');
    }
    return op;
}

bool check_cliente(const map<string,Cliente>& clientes, const string& codigo){
    for(auto i: clientes)
        if(i.first == codigo) return true;
    return false;
}

bool check_produto(const map<string,Combustivel>& produtos, const string& codigo){
    for(auto i: produtos)
        if(i.first == codigo) return true;
    return false;
}

void venda(vector<Venda>& vendas,
           map<string,Cliente>clientes,
           map<string,Combustivel>combustiveis){
    cout << "\n>>> VENDA <<<\n\n";
    Venda venda;
    string codigo, pago;
    double preco, total;
    cout << "Data da compra        : ";
    getline(cin, venda.data);
    cout << "Codigo do cliente     : ";
    getline(cin, codigo);
    if(check_cliente(clientes, codigo)){
        if(!clientes[codigo].ativo){
            cout << "\n>>> Cliente nao esta ativo. Venda nao pode ser feita <<<\n" ;  
            return;           
        }
        venda.cod_cliente = codigo;
    }
    else{
        cout << "\n>>> Cliente nao cadastrado <<<\n" ; 
        return;       
    }
    cout << "Codigo do combustivel : ";
    getline(cin, codigo);
    if(check_produto(combustiveis, codigo)){
        venda.cod_produto = codigo;
        venda.valor_do_litro = combustiveis[codigo].preco;
        cout << "Preco por litro       :" << venda.valor_do_litro << '\n';    
    }
    else{
        cout << "\n>>> Combustivel nao cadastrado <<<\n" ; 
        return;       
    }
    cout << "Quantidade comprada   : ";
    cin >> venda.quantidade;
    cout << "Valor a pagar         : ";
    cout << (venda.total = venda.valor_do_litro * venda.quantidade) << '\n';    
    cout << "Responsavel pela venda: ";
    getline(cin, venda.responsavel);
    //cin.ignore(256, '\n');
    cout << "Pagamento (0 nao pago; qualquer outro valor significa pago: ";
    getline(cin, pago);
    if(pago == "0")
        venda.pago = false; 
    else
        venda.pago = true; 

    vendas.push_back(venda);     
}

void listar_abertos(const vector<Venda>& vendas){
    cout << "\n>>> LISTAR PEDIDOS EM ABERTO <<<\n\n";
    for(auto i: vendas)
        if(!i.pago)
            i.print();
}

void listar_todos(const vector<Venda>& vendas){
    cout << "\n>>> LISTAR TODOS OS PEDIDOS <<<\n\n";
    for(auto i: vendas)
        i.print();
}

void listar_clientes(const map<string, Cliente>& m){
    cout << "\n>>> CLIENTES <<<\n\n";
    for(auto i: m)
        i.second.print();
}

void listar_combustiveis(const map<string, Combustivel>& m){
    cout << "\n>>> COMBUSTIVEIS <<<\n\n";
    for(auto i: m)
        i.second.print();
}

void cadastrar_cliente(map<string, Cliente>& m){
    cout << "\n>>> CADASTRAR CLIENTE <<<\n\n";
    Cliente novo_cliente;
    cout << "Codigo: ";
    getline(cin, novo_cliente.cod_cliente);
    cout << "Nome: ";
    getline(cin, novo_cliente.nome);
    novo_cliente.ativo = true;

    m.insert(pair<string, Cliente>(novo_cliente.cod_cliente, novo_cliente));
}

void ativar_desativar_cliente(map<string, Cliente>& m){
    cout << "\n>>> ATIVAR/DESATIVAR CLIENTE <<<\n\n"; 
    string cod;
    cout << "Codigo: ";
    getline(cin, cod);

    auto it = m.find(cod);
      
    if(it == m.end())
        cout << "\n>>> Cliente nao cadastrado <<<\n" ;
    else{
        it->second.print();
        string s;
        cout << "Entre com 0 para desativar ou qualquer outro valor para ativar: "; 
        getline(cin, s);
        if(s == "0")
            it->second.ativo = false; 
        else
            it->second.ativo = true;  
    } 
}

int main(){

    map<string,Cliente>clientes;
    map<string,Combustivel>combustiveis;
    vector<Venda>vendas;

    init(clientes, combustiveis);

    while(true){
        int op = menu();
        if(!op)break;
        switch(op){
            case 1: venda(vendas,clientes,combustiveis); break;
            case 2: listar_abertos(vendas); break;
            case 3: listar_todos(vendas); break;
            case 4: listar_clientes(clientes); break;
            case 5: listar_combustiveis(combustiveis); break;
            case 6: cadastrar_cliente(clientes);break;
            case 7: ativar_desativar_cliente(clientes);break;
        }
    }

    return 0;
}