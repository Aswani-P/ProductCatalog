PRODUCT_COUNT = 3
GIFT_WRAP_FEE_PER_PRODUCT = 1
SHIPPING_FEE_PER_PACKAGE = 5
PRODUCT_PER_PACKAGE = 10

class Products:
    def __init__(self,name,price,quantity,total,need_wraper):
        self.product_name = name
        self.price=price
        self.product_quantity=quantity
        self.product_total=total
        self.need_wraper=need_wraper

class Discount:
    def __init__(self,name,amount):
        self.name=name
        self.amount=amount

class Cart:
    def __init__(self):
        self.products=[]
        self.discount_applied=Discount("NO DISCOUNT",0)
        self.cart_quantity=0
        self.cart_total=0
        self.wraped_product_count=0
        self.gift_wrap_fee=0
        self.package_count=0
        self.shipping_fee=0
        self.grand_total=0

product_details =[
    Products("produt A", 20, 0, 0, 0),
    Products("product B", 40, 0, 0, 0),
    Products("product C", 50, 0, 0, 0)
]

cart=Cart()

def getProducts():
    for i in range(PRODUCT_COUNT):
        cart.products.append(product_details[i])
        getProductQuantity(i)
        getProductNeedWarper(i)
        getProductTotal(i)
        
    
def getProductQuantity(productNumber):
    cart.products[productNumber].product_quantity= int(input(f"Enter the quantity of {cart.products[productNumber].product_name} is: "))

def getProductNeedWarper(productNumber):
    need_wraper = int(input(f"Wrap{cart.products[productNumber].product_name} as a gift ?(1 for yes/0 for no)")) 
    if need_wraper == 1 or need_wraper == 0:
        cart.products[productNumber].need_wraper=need_wraper
    else:
        print("Please enter the correct value. (1 for yes or 0 for no )")
        getProductNeedWarper(productNumber)

def getProductTotal(productNumber):
    cart.products[productNumber].product_total = cart.products[productNumber].product_quantity * cart.products[productNumber].price

def getcartTotal():
    for i in range(PRODUCT_COUNT):
        cart.cart_total+=cart.products[i].product_total

def getcartQuantity():
    for i in range(PRODUCT_COUNT):
        cart.cart_quantity+=cart.products[i].product_quantity
def getPackageCount():
    cart.package_count=cart.cart_quantity//PRODUCT_PER_PACKAGE
    if cart.cart_quantity % PRODUCT_PER_PACKAGE !=0:
        cart.package_count+=1

def getShippingFee():
    cart.shipping_fee= cart.package_count * SHIPPING_FEE_PER_PACKAGE

def getWrappedProductCount():
    for i in range(PRODUCT_COUNT):
        if cart.products[i].need_wraper ==1:
            cart.wraped_product_count +=cart.products[i].product_quantity

def getGiftwrapFee():
    cart.gift_wrap_fee = cart.wraped_product_count * GIFT_WRAP_FEE_PER_PRODUCT


def getDiscountDisplayed():
     discount = Discount("NO DISCOUNT",0)
     discount = maxDiscount(discount,getflat10discount())
     discount= maxDiscount(discount,getbulk5discount())
     discount = maxDiscount(discount,getbulk10discount())
     discount = maxDiscount(discount,getTierd50discount())
     cart.discount_applied =discount

def maxDiscount(discount_1,discount_2):
    if discount_1.amount >= discount_2.amount:
        return discount_1
    else:
        return discount_2


def getflat10discount():
    discount= Discount("flat-10-discount",0)
    if cart.cart_total > 200:
        discount.amount=10
    discountDetails(discount)
    return discount


def getbulk5discount():
    discount= Discount("bulk-5-discount",0)
    for i in range(PRODUCT_COUNT):
        if cart.products[i].product_quantity > 10:
            discount.amount= int(cart.products[i].product_total*0.05)
            break
    discountDetails(discount)
    return discount

def getbulk10discount():
    discount = Discount("bulk-10-discount",0)
    if cart.cart_quantity > 20:
        discount.amount= int(cart.cart_total*0.1)
    discountDetails(discount)
    return discount
    
def getTierd50discount():
    discount=Discount("tierd-50-discount",0)
    discount_amount=0
   
    if cart.cart_quantity > 30:
         for i in range(PRODUCT_COUNT):
             if cart.products[i].product_quantity > 15:
                 discount_amount += int(cart.products[i].product_total * 0.5)
    discount.amount=discount_amount
    discountDetails(discount)
    return discount



def discountDetails(discount):
    print(f"Discount  \"{discount.name} \"is {'applicable' if discount.amount > 0 else 'not appliable'}")
    print(f" Discount amount: {discount.amount}")





def getgrandTotal():
    cart.grand_total = cart.cart_total - cart.discount_applied.amount + cart.shipping_fee + cart.gift_wrap_fee

def display():
    for i in range(PRODUCT_COUNT):
        print(f"Product name : {cart.products[i].product_name} \t Quantity : {cart.products[i].product_quantity} \t Total:{cart.products[i].product_total} ")
    print(f"Subtotal: {cart.cart_total}")
    print(f"Discount Applied :{cart.discount_applied.name}")
    print(f"Discount amount:{cart.discount_applied.amount}")
    print(f"Shipping fee:{cart.shipping_fee}")
    print(f"Gift wrap fee: {cart.gift_wrap_fee}")
    print(f"Total: {cart.grand_total}")


def main():
    getProducts()
    getcartTotal()
    getcartQuantity()
    getPackageCount()
    getShippingFee()
    getWrappedProductCount()
    getGiftwrapFee()
    getDiscountDisplayed()
    getgrandTotal()
    display()
    

if __name__ =="__main__":
    main()







