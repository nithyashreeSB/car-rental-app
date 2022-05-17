#pragma once

#include <string>
#include <iostream>
#include <pqxx/pqxx>
#include <exception>
using std::string;
using std::cout;
using std::cin;
using std::endl;
using namespace std;
class car
{
public:
    int n;
    string brand;
    int rent;
    string SUV;
    string sedan;
    void insert();
    void update();
    void remove();
    void select();
    void show();
    int login_check();
}ca;
int car::login_check()
{
    string connectionString = "host=localhost port=5432 dbname=car user=postgres password =1312";
    cout << "Please enter user id" << endl;
    string user, model;
    int password, flag = 0;
    cin >> user;
    cout << "Please enter password" << endl;
    cin >> password;
    string quer = " SELECT * FROM login WHERE pass_word = ";
    quer += std::to_string(password);

    pqxx::connection connectionObject(connectionString.c_str());

    pqxx::work login(connectionObject);

    pqxx::result response = login.exec(quer);

    for (int i = 0; i < response.size(); i++)
    {
        flag = 1;
    }

    if (flag == 1)
    {
        cout << "login approved\n" << endl;
        return 1;
    }
    else
    {
        cout << "invalid password" << endl;
        return 0;
        
    }

}
void car::show()
{
    string connectionString = "host=localhost port=5432 dbname=car user=postgres password =1312";
    
    pqxx::connection connectionObject(connectionString.c_str());
    pqxx::work car_details(connectionObject);
    pqxx::result response = car_details.exec("SELECT * FROM car_details");

    cout << "reg_no" << "\t" << "Brand" << "\t" << "rent" << "\t" << "SUV" << "\t" << "sedan\n" << endl;

    for (int i = 0; i < response.size(); i++)
    {
        cout << response[i][0] << "\t" << response[i][1] << "\t" << response[i][2] << "\t" << response[i][3] << "\t" << response[i][4] << endl;
    }

}
void car::select()
{
    cout << "Type the brand of the car you are searching for (please type using capital letters)" << endl;
    cin >> brand;
    string connectionString = "host=localhost port=5432 dbname=car user=postgres password =1312";

    pqxx::connection connectionObject(connectionString.c_str());
    pqxx::work car_details(connectionObject);

    string sql = "SELECT *FROM car_details WHERE car_brand='" + brand + "'";
    pqxx::result response = car_details.exec(sql);

    for (int i = 0; i < response.size(); i++)
    {
        cout << response[i][0] << "\t" << response[i][1] << "\t" << response[i][2] << "\t" << response[i][3] << "\t" << response[i][4] << endl;
    }

}
void car::remove()
{
    string connectionString = "host=localhost port=5432 dbname=car user=postgres password =1312";
 
    cout<< "Please type the brand of the car you had selected" << endl;
    cin >> brand;
    pqxx::connection connectionObject(connectionString.c_str());

    pqxx::work car_details(connectionObject);

    pqxx::result response = car_details.exec("DELETE FROM car_details WHERE car_brand = '" +brand+ "'");

    car_details.commit();


}

void car::update()
{
    try
    {
        string connectionString = "host=localhost port=5432 dbname=car user=postgres password =1312";
        pqxx::connection connectionObject(connectionString.c_str());

        pqxx::work car_details(connectionObject);
        cout << "Enter the reg number" << endl;
        cin >> n;
        cout << "Enter the brand" << endl;
        cin >> brand;
        cout << "Enter the rent amount" << endl;
        cin >> rent;
        cout << "SUV" << endl;
        cin >> SUV;
        cout << "Sedan" << endl;
        cin >> sedan;
        string sql = "UPDATE car_details SET reg_no=" + to_string(n) + ", car_brand='" + brand + "', price='" + to_string(rent) + "',suv='" + SUV + "',sedan='" + sedan + "' WHERE reg_no=" + to_string(n) + "";
        pqxx::result response = car_details.exec(sql);
        car_details.commit();
        cout << "Updated Successfully";
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

}
void car::insert()
{
    try
    {
        string connectionString = "host=localhost port=5432 dbname=car user=postgres password =1312";
        pqxx::connection connectionObject(connectionString.c_str());

        pqxx::work car_details(connectionObject);
        cout << "Enter the reg number" << endl;
        cin >> n;
        cout << "Enter the brand" << endl;
        cin >> brand;
        cout << "Enter the rent amount" << endl;
        cin >> rent;
        cout << "SUV" << endl;
        cin >> SUV;
        cout << "Sedan" << endl;
        cin >> sedan;
        pqxx::result response = car_details.exec("INSERT INTO car_details (reg_no,car_brand,price,suv,sedan) VALUES(" + to_string(n) + ",'" + brand + "','" +to_string(rent) + "','" + SUV + "','" + sedan + "')");
        car_details.commit();
        cout << "Sucessfully inseterted" << endl;
    }

    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

   
}

int main()
{
    string connectionString = "host=localhost port=5432 dbname=car user=postgres password =1312";
    int lc,a;
    cout << "type 1 to book car" << endl;
    cout << "type the secret code for admin" << endl;
    cin >> a;
    if (a == 1)
    {
        lc = ca.login_check();
        if (lc == 0)
        {
            return 0;
        }
        int k1;
        cout << "Press 1 to view all car" << endl;
        cout << "Press 2 to select car from list" << endl;
        cin >> k1;
        if (k1 == 1)
        {
            ca.show();
        }
        if (k1 == 2)
        {
           ca.select();
        }
        ca.remove();
        cout << "Thankyou" << endl;
    }
    else if (a == 147852)
    {
        cout << "Press 1 to uptate an entry" << endl;
        cout << "Press 2 to delete an entry" << endl;
        cout << "Press 3 to search " << endl;
        cout << "Press 4 to insert" << endl;
        int c;
        cin >> c;
        switch (c)
        {
        case 1:
        {
            ca.update();
            break;
        }
        case 2:
        {
            ca.remove();
            cout << "sucessfully deleted" << endl;
            break;
        }
        case 3:
        {
            ca.select();
            break;
        }
        case 4:
        {
            ca.insert();
            break;
        }
        
        }
    }

}