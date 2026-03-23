#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Colors
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"

//Structure 
typedef struct {
    double principal;
    double annual_rate;
    int years;
    int compounding_freq;} 
    FinanceData;

//Clear input buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);}

//Calculation functions
double calculate_fv(FinanceData data) {
    double r = (data.annual_rate / 100.0) / data.compounding_freq;
    int n = data.compounding_freq * data.years;
    return data.principal * pow(1 + r, n);}

double calculate_emi(double principal, double annual_rate, int months) {
    if (months <= 0) return 0.0;
    double monthly_rate = annual_rate / (12.0 * 100.0);
    return (principal * monthly_rate * pow(1 + monthly_rate, months)) /
           (pow(1 + monthly_rate, months) - 1);}

double calculate_pv_single(double future_value, double annual_rate, int years) {
    return future_value / pow(1 + (annual_rate / 100.0), years);}

double calculate_pv_annuity(double pmt, double annual_rate, int periods) {
    if (periods <= 0) return 0.0;
    double monthly_rate = annual_rate / (12.0 * 100.0);
    return pmt * (1 - pow(1 + monthly_rate, -periods)) / monthly_rate;}

// UI functions
void print_header() {
    printf("\n");
    printf("%s  FINANCIAL CALCULATOR %s\n", CYAN, RESET);}

void print_menu() {
    printf("\n%sMain Menu:%s\n", RED, RESET);
    printf("%s1.%s Compound Interest (Future Value)\n", YELLOW, RESET);
    printf("%s2.%s Loan EMI Calculator\n", YELLOW, RESET);
    printf("%s3.%s Present Value Calculator\n", YELLOW, RESET);
    printf("%s4.%s Future Value of Regular Deposits\n", YELLOW, RESET);
    printf("%s5.%s Exit\n", YELLOW, RESET);
    printf("\n%sEnter your choice (1-5): %s", GREEN, RESET);}

int main() {
    int choice;

    while (1) {
        print_header();
        print_menu();

        if (scanf("%d", &choice) != 1) {
            printf("%sInvalid input! Please enter a number.%s\n", RED, RESET);
            clear_input_buffer();
            continue;}

        if (choice == 5) {
            printf("\n%sThank you for using the Financial Calculator. Goodbye!%s\n", GREEN, RESET);
            break;}

        switch (choice) {
            case 1: { // Compound Interest
                FinanceData data = {0};
                printf("\n%s Compound Interest Calculator %s\n", MAGENTA, RESET);
                printf("Enter Principal Amount: ");
                scanf("%lf", &data.principal);
                printf("Enter Annual Rate (%): ");
                scanf("%lf", &data.annual_rate);
                printf("Enter Years: ");
                scanf("%d", &data.years);
                printf("Compounding frequency (1=Yearly, 12=Monthly, 365=Daily): ");
                scanf("%d", &data.compounding_freq);
                if (data.principal <= 0 || data.years <= 0 || data.compounding_freq <= 0) {
                    printf("%sError: Invalid input values.%s\n", RED, RESET);
                    break;}

                double fv = calculate_fv(data);
                printf("\n%sResults:%s\n", GREEN, RESET);
                printf("Future Value    : %.2f\n", fv);
                printf("Interest Earned : %.2f\n", fv - data.principal);
                break;}

            case 2: { // EMI
                double p, r;
                int m;
                printf("\n%s Loan EMI Calculator %s\n", MAGENTA, RESET);
                printf("Enter Loan Amount: ");
                scanf("%lf", &p);
                printf("Enter Annual Interest Rate: ");
                scanf("%lf", &r);
                printf("Enter Number of Months: ");
                scanf("%d", &m);

                if (p <= 0 || m <= 0) {
                    printf("%sError: Invalid input.%s\n", RED, RESET);
                    break;}

                double emi = calculate_emi(p, r, m);
                double total = emi * m;
                printf("\n%sResults:%s\n", GREEN, RESET);
                printf("Monthly EMI     : %.2f\n", emi);
                printf("Total Payment   : %.2f\n", total);
                printf("Total Interest  : %.2f\n", total - p);
                break;}

            case 3: { // Present Value
                int pv_choice;
                printf("\n%s Present Value Calculator %s\n", MAGENTA, RESET);
                printf("1. Present Value of Single Future Amount\n");
                printf("2. Present Value of Annuity (Regular Payments)\n");
                printf("Choose (1 or 2): ");
                scanf("%d", &pv_choice);

                if (pv_choice == 1) {
                    double fv_amount, rate;
                    int years;
                    printf("Enter Future Value: ");
                    scanf("%lf", &fv_amount);
                    printf("Enter Annual Discount Rate (%%): ");
                    scanf("%lf", &rate);
                    printf("Enter Years: ");
                    scanf("%d", &years);

                    double pv = calculate_pv_single(fv_amount, rate, years);
                    printf("\n%sPresent Value: %.2f%s\n", GREEN, pv, RESET);
                }
                else if (pv_choice == 2) {
                    double pmt, rate;
                    int periods;
                    printf("Enter Monthly Payment: ");
                    scanf("%lf", &pmt);
                    printf("Enter Annual Discount Rate: ");
                    scanf("%lf", &rate);
                    printf("Enter Number of Months: ");
                    scanf("%d", &periods);

                    double pv = calculate_pv_annuity(pmt, rate, periods);
                    printf("\n%sPresent Value of Annuity: %.2f%s\n", GREEN, pv, RESET);}
                else {
                    printf("%sInvalid choice.%s\n", RED, RESET);}
                break;}

            case 4: { // Future Value of Annuity
                double pmt, rate;
                int periods;
                printf("\n%s Future Value of Regular Deposits %s\n", MAGENTA, RESET);
                printf("Enter Monthly Deposit: ");
                scanf("%lf", &pmt);
                printf("Enter Annual Interest Rate: ");
                scanf("%lf", &rate);
                printf("Enter Number of Months: ");
                scanf("%d", &periods);

                if (pmt <= 0 || periods <= 0) {
                    printf("%sError: Invalid input.%s\n", RED, RESET);
                    break;}

     double r = rate / (12.0 * 100.0);
     double fv = pmt * (pow(1 + r, periods) - 1) / r;
                printf("\n%sFuture Value: %.2f%s\n", GREEN, fv, RESET);
                break;}

            default:
                printf("%sInvalid option! Please choose 1 to 5.%s\n", RED, RESET);}

        printf("\n%sPress Enter to return to menu...%s", YELLOW, RESET);
        clear_input_buffer();
        getchar();}

return 0;}
