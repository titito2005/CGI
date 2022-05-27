async function deleteItem(itemId){
    const params = "sellId="+itemId;
    const response = await fetch("http://172.24.131.194/cgi-bin/cart", {
        method: "DELETE",
        headers: {
            "Content-type": "application/x-www-form-urlencoded; charset=UTF-8"
        },
        body: params
    })
    alert("Producto eliminado del carrito");
    document.location.reload();
}