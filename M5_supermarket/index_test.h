const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>PAY</title>
    <style>
        .box{
            display: -webkit-flex;
            display: flex;
            flex-direction: column;
            position: absolute;
            left: 0px;
            top:0px;
            width: 100%;
            height: 100%;;            
            background-color:#e8e8e8;
            justify-content:space-between;
        }
        .title{
            padding: 20px 30px 20px 30px;
            background-color: #ff7c62;
            color: white;
            margin-top:0px;
            margin-bottom:0px;
        }
        .content{
            margin-top: 10px;
            height: 500px;
            overflow-y:scroll; 
        }
        .content div{
            margin-top: 10px;
            border-radius: 10px;
            margin: 10px;
            background-color:white;
            padding: 15px;
            display: flex;
            flex-direction: row;
            justify-content: space-between;
            transition: all .5s ease;
        }

        .content div.clear{
            transform: translateX(110%);
            opacity: 0.3;
        }

        .foot{
            display: -webkit-flex;
            display: flex;
            flex-direction:row;
            justify-content: space-between;
            background-color:white;
            padding: 10px 30px 10px 30px;
            border-radius: 10px;
            margin: 10px;
            margin-bottom:20px;
        }
        .btn {
            margin: 10px;
        }
        .btn h3 {
            padding: 10px;
            border-radius: 10px;
            background-color: #ff7c62;
            color: white;
        }


        .total_price{
            display: flex;
            flex-direction: column;
        }
        .keyboard{
            display: flex;
            flex-direction: column;
        }
        .keyboard div{
            display: flex;
            flex-direction: row;
            justify-content:space-between;
        }
        .keyboard div h3{
            padding: 30px;
            margin: 0px;
        }
    </style>
</head>
<body>
    <div class="box">
        <h3 class="title" onclick="get_list()">Shopping List</h3>
        <div class="content">
            <div><h3 style="margin: 10px">Empty Shopping Cart</h3></div>
        </div>
        <div class="foot">
            <div class="total">
                <h3>Total Price</h3>
                <h2 style="text-align: center;">xxx</h2>
            </div>
            <div class="btn"><h3>>Click to Pay</h3></div>
        </div>
    </div>
</body>
<script>


function price_handle(product_name,product_weight){
    if(product_name == "watchband"){
        return product_weight*2
    }else if(product_name == "big-orange-wheel"){
        return product_weight*4
    }else if(product_name == "orange-wheel"){
        return product_weight*6
    }else if(product_name == "mecanum-wheel"){
        return product_weight*8
    }else if(product_name == "big-blue-wheel"){
        return product_weight*5
    }else if(product_name == "servo"){
        return product_weight*1
    }else if(product_name == "white-wheel"){
        return product_weight*7
    }
}



function sleep(delay){
    var start = new Date().getTime();
    while (new Date().getTime() < start + delay);
}

var httpRequest;

function get_list(){

    if(window.XMLHttpRequest) {
        httpRequest = new XMLHttpRequest();
    }else if(window.ActiveXObject) {
        httpRequest = new ActiveXObject();
    }
    
    httpRequest.open("GET", "/get_list", true);

    httpRequest.onreadystatechange = res_handle;

    httpRequest.send();
}


function res_handle(){
    if(httpRequest.readyState==4) {
        if(httpRequest.status==200) {
            var product_list = httpRequest.responseText;
            var old_list = document.getElementsByClassName("content")[0].innerHTML = '';
            if(product_list == "ok"){
                var old_list = document.getElementsByClassName("content")[0].innerHTML = '<div><h3 style="margin: 10px">Empty Shopping Cart</h3></div>';
                document.getElementsByClassName("btn")[0].getElementsByTagName("h3")[0].innerHTML="Already Paid";
                document.getElementsByClassName("btn")[0].getElementsByTagName("h3")[0].style.backgroundColor="#007bff";
                document.getElementsByClassName("total")[0].getElementsByTagName("h2")[0].innerHTML= "0￥";
            }
            else{
                var data = JSON.parse(product_list);
                var total_price = 0;
                for(var key in data){
                    var prduct_price = price_handle(key,data[key]);
                    var item_str = "<span>"+key+"("+data[key]+")g</span><span>"+prduct_price+"￥</span>";
                    var div_tag = document.createElement('div');
                    div_tag.insertAdjacentHTML("beforeEnd", item_str);
                    document.getElementsByClassName("content")[0].appendChild(div_tag);
                    total_price += prduct_price;
                }
                document.getElementsByClassName("total")[0].getElementsByTagName("h2")[0].innerHTML= total_price+"￥";
            }
        }
    }
}


function Paid(){
    if(window.XMLHttpRequest) {
        httpRequest = new XMLHttpRequest();
    }else if(window.ActiveXObject) {
        httpRequest = new ActiveXObject();
    }
    httpRequest.open("GET", "/paid", true);
    httpRequest.onreadystatechange = res_handle;
    httpRequest.send();
}



function Pay(){
    var old_list = document.getElementsByClassName("content")[0].getElementsByTagName("div");
    var i = 0;
    var t1 = setInterval(function () {
        if(old_list.length>i){
            old_list[i].className = 'clear';
            i++;
        }else
        {
            window.clearInterval(t1);
            old_list = document.getElementsByClassName("content")[0].innerHTML = '';
            document.getElementsByClassName("btn")[0].removeEventListener("onclick",Pay);
            Paid();
        }
    }, 200);

}

document.getElementsByClassName("btn")[0].onclick=function(){Pay()};


get_list();


</script>
</html>
)=====";
