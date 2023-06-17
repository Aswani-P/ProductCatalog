#include <stdio.h>

const int PRODUCT_COUNT = 3;
const int GIFT_WRAPE_FEE_PER_PRODUCT = 1;
const int SHIPPING_FEE_PER_PACKAGE = 5;
const int PRODUCT_PER_PACKAGE = 10;

typedef struct{
    char productname[20];
    int price;
    int product_quantity;
    int product_total;
    int need_wraper; 
}Product;

typedef struct{
    char name[20];
    int amount;
}Discount;

typedef struct{
    Product products[3];
    Discount discount_applyed;
    int cart_quantity;
    int cart_total;
    
    int wraped_product_count;
    int gift_wrap_fee;
    int package_count;
    int shipping_fee;

    int grand_total;
}Cart;

Product product_details[] = {
    {"Product A", 20, 0, 0, 0 },
    {"Product B", 40, 0, 0, 0 },
    {"Product C", 50, 0, 0, 0 }
};

Cart cart;

void getProducts();
void getProductQuantity(int);
void getProductNeedWarper(int);
void getProductTotal(int);
void getCartTotal();
void getCartQuanitity();
void getPackageCount();
void getShippingFee();
void getWrapedProductCount();
void getGiftWrapFee();
void getDiscountApplyed();
Discount getFlat10Discount();
Discount getBulk5Discount();
Discount getBulk10Discount();
Discount getTiered50Discount();
Discount returnMaxDis(Discount discount_1, Discount discount_2);
void discountDetails(Discount);
void getGrandTotal();    
void displayBill();


void main() {
    getProducts();
    getCartTotal();
    getCartQuanitity();
    getPackageCount();
    getShippingFee();
    getWrapedProductCount();
    getGiftWrapFee();
    getDiscountApplyed();
    getGrandTotal();
    displayBill();
}

void getProducts(){
    for (int i=0; i<PRODUCT_COUNT; i++){
        cart.products[i] = product_details[i];
        getProductQuantity(i);
        getProductNeedWarper(i);
        getProductTotal(i);
    }
}
void getProductQuantity(int productNumber ){
    printf("Enter the quantity of %s : ", cart.products[productNumber].productname);
    scanf("%d", &cart.products[productNumber].product_quantity);
}
void getProductNeedWarper(int productNumber ){
    int need_wraper;
    printf("Wrap %s as a gift? (1/0) : ", cart.products[productNumber].productname);
    scanf("%d", &need_wraper);
    if (need_wraper==1||need_wraper==0){
        cart.products[productNumber].need_wraper = need_wraper;
    }else{
        printf("(Please enter 1 for yes/ 0 for no)\n");
        getProductNeedWarper(productNumber);
    }
}
void getProductTotal(int productNumber ){
    cart.products[productNumber].product_total = 
        cart.products[productNumber].price * 
        cart.products[productNumber].product_quantity;
}

void getCartTotal(){
    for (int i=0; i<PRODUCT_COUNT; i++)
        cart.cart_total+=cart.products[i].product_total;
}

void getCartQuanitity(){
    for (int i=0; i<PRODUCT_COUNT; i++)
        cart.cart_quantity+=cart.products[i].product_quantity;
}

void getPackageCount(){
    cart.package_count = cart.cart_quantity/PRODUCT_PER_PACKAGE;
    if(cart.cart_quantity%PRODUCT_PER_PACKAGE!=0)
        cart.package_count+=1;
}

void getShippingFee(){
    cart.shipping_fee = cart.package_count * SHIPPING_FEE_PER_PACKAGE;
}

void getWrapedProductCount(){
    for (int i=0; i<PRODUCT_COUNT; i++)
        if(cart.products[i].need_wraper==1)
            cart.wraped_product_count+=cart.products[i].product_quantity;
}

void getGiftWrapFee(){
    cart.gift_wrap_fee = cart.wraped_product_count * GIFT_WRAPE_FEE_PER_PRODUCT;
}

void getDiscountApplyed(){
    printf("\n");
    Discount discount = { "NO DISCOUNT", 0 };
    discount = returnMaxDis(discount, getFlat10Discount());
    discount = returnMaxDis(discount, getBulk5Discount());
    discount = returnMaxDis(discount, getBulk10Discount());
    discount = returnMaxDis(discount, getTiered50Discount());
    cart.discount_applyed = discount;
}
Discount returnMaxDis(Discount discount_1, Discount discount_2){
    return discount_1.amount >= discount_2.amount ?
        discount_1 : discount_2;
}
Discount getFlat10Discount(){
    Discount discount = { "flat_10_discount", 0 };
    if(cart.cart_total>200)
        discount.amount = 10;
    discountDetails(discount);
    return discount;
}
Discount getBulk5Discount(){
    Discount discount = { "bulk_5_discount", 0 };
    for (int i=0; i<PRODUCT_COUNT; i++)
        if(cart.products[i].product_quantity>10){
            discount.amount = cart.products[i].product_total*0.05;
            break;
        }
    discountDetails(discount);
    return discount;
}
Discount getBulk10Discount(){
    Discount discount = { "bulk_10_discount", 0 };
    if(cart.cart_quantity>20)
        discount.amount = cart.cart_total*0.1;
    discountDetails(discount);
    return discount;
}
Discount getTiered50Discount(){
    Discount discount = { "tiered_50_discount", 0 };
    int discount_amount = 0;
    if(cart.cart_quantity>30)
        for (int i=0; i<PRODUCT_COUNT; i++)
            if(cart.products[i].product_quantity > 15)
                discount_amount += cart.products[i].product_total * 0.5;

    discount.amount = discount_amount;
    discountDetails(discount);
    return discount;
}
void discountDetails(Discount discount){
    printf("Discount \"%s\" is %s", discount.name, 
        discount.amount>0 ? "applicable\n" : "not applicable\n");
    printf("\tDiscount Amount : %d\n", discount.amount);
}

void getGrandTotal(){
    cart.grand_total = cart.cart_total - 
        cart.discount_applyed.amount +
        cart.gift_wrap_fee +
        cart.shipping_fee;
}

void displayBill(){
    printf("\n\n");
    printf("                    BILL\n");
    printf("                    ----\n");

    for (int i=0; i<PRODUCT_COUNT; i++)
        printf("%s: \tQuantity = %d\tTotal = $%d\n", 
            cart.products[i].productname,
            cart.products[i].product_quantity,
            cart.products[i].product_total);

    printf("Subtotal         : $%d\n", cart.cart_total);
    printf("Discount applied : %s\n", cart.discount_applyed.name);
    printf("Discount amount  : $%d\n", cart.discount_applyed.amount);
    printf("Shipping fee     : $%d\n", cart.shipping_fee);
    printf("Gift wrap fee    : $%d\n", cart.gift_wrap_fee);
    printf("Total            : $%d\n", cart.grand_total );
}  
