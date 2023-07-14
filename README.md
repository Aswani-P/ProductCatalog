
README

==============================

Program Name: Product Catalog and Pricing

Description:
This program calculates the total cost, discounts, shipping fees, and gift wrap fees based on a given catalog of products and a set of discount rules. It allows the user to input the quantity of each product and specify whether each product should be wrapped as a gift. The program then calculates the subtotal, discount amount, shipping fee, and total cost, and displays the detailed breakdown of each component.

Catalog:
Product Name    Price
Product A       $20
Product B       $40
Product C       $50

Discount Rules:
- flat_10_discount: If the cart total exceeds $200, apply a flat $10 discount on the cart total.
- bulk_5_discount: If the quantity of any single product exceeds 10 units, apply a 5% discount on that item's total price.
- bulk_10_discount: If the total quantity exceeds 20 units, apply a 10% discount on the cart total.
- tiered_50_discount: If the total quantity exceeds 30 units and any single product quantity is greater than 15, apply a 50% discount on the products that have a quantity above 15. The first 15 units retain the original price, while units above 15 receive a 50% discount.

Fees:
- Gift wrap fee: $1 per unit.
- Shipping fee: 10 units can be packed in one package, and the shipping fee for each package is $5.

Usage:
1. Compile the program using a C compiler, such as GCC, by running the following command in the terminal:
   $ gcc product_catalog.c -o product_catalog

2. Run the program and follow the prompts to enter the quantity and gift wrapping preference for each product.

3. After entering the required information, the program will display the following details:
   - Product name, quantity, and total amount for each product.
   - Subtotal of the cart.
   - The discount name applied and the discount amount.
   - The shipping fee and the gift wrap fee.
   - The total cost of the cart.

Author:
Aswani P

Additional Notes:
- The program considers only one discount rule per purchase and applies the most beneficial one for the customer.
- If multiple discounts are applicable, the program calculates the discount amount for each rule and selects the one with the highest discount.
- Ensure that the input for the quantity of each product is a positive integer.
- The program performs basic error handling and input validation, such as checking for non-integer inputs and negative quantities.

