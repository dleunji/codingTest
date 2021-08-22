using namespace std;

long long solution(int price, int money, int count)
{
    long long lack = ((long long)price * count * (count + 1) / 2) - (long long)money;
    if(lack <= 0) return 0;
    return lack;
}