async function deleteItem(itemId){
    alert(itemId);
    const params = "sellId="+itemId;
    const response = await fetch("http://localhost/cgi-bin/cart", {
        method: "DELETE",
        headers: {
            "Content-type": "application/x-www-form-urlencoded; charset=UTF-8"
        },
        body: params
    })
}