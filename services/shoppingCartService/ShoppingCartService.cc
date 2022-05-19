#include "ShoppingCartService.h"

ShoppingCartService::ShoppingCartService()
{
    db = new Database();
    if (db->connectToDatabase())
    {
        conn = db->getConnection();
    }
    else
    {
        printf("%s \n", "Error conectando a la base de datos");
        exit(1);
    }
}

ShoppingCartService::~ShoppingCartService()
{
}

vector<ShoppingCart> ShoppingCartService::getAllShoppingCartByUserId(string id)
{
    vector<ShoppingCart> userCart;
    MYSQL_ROW row;
    string query = "SELECT * FROM shoppingCart WHERE userId = ";
    query.append("'");
    query.append(id);
    query.append("'");
    const char *finalQuery = query.c_str();
    // Return 0 for success
    if (!mysql_query(conn, finalQuery))
    {
        res = mysql_use_result(conn);
        // Fetch a result set
        while ((row = mysql_fetch_row(res)) != NULL)
        {
            ShoppingCart cart;
            cart.setId(row[0]);
            cart.setUserId(row[1]);
            cart.setSellId(row[2]);
            cart.setSellCant(row[3]);
            cart.setCreatedAt(row[4]);
            userCart.push_back(cart);
        }
        // Release memories
        mysql_free_result(res);
    }
    return userCart;
}
bool ShoppingCartService::addShoppingCart(string idUser, string idSell)
{
    bool addShoppingCar = false;
    string query = "INSERT INTO shoppingCart (userId, sellId)VALUES(";
    query.append("'" + idUser + "','" + idSell + "')");
    const char *finalQuery = query.c_str();
    if (!mysql_query(conn, finalQuery))
    {
        addShoppingCar = true;
    }

    return addShoppingCar;
}
