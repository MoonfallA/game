#include <iostream>
#include <ctime>
using namespace std;

int randomnum()
{
	int num[4];
	bool isused[10] = { true };
	srand(time(0));
	int ans = 0;
	for (int i = 0; i < 4; i++)
	{
		while (isused[ans])
		{
			ans = rand() % 9 + 1;
		}
		num[i] = ans;
		isused[ans] = true;
	}
	return num[0] * 1000 + num[1] * 100 + num[2] * 10 + num[3];
}
bool input(int guess)
{
	if (guess < 1000 || guess>9999)
	{
		return false;
	}

	int digits[4];
	int temp = guess;
	bool used[10] = { false };

	for (int i = 3; i >= 0; i--) {
		digits[i] = temp % 10;
		temp /= 10;

		// 检查是否包含0或重复数字
		if (digits[i] == 0 || used[digits[i]]) {
			return false;
		}
		used[digits[i]] = true;
	}
	return true;
}

void  compare(int ans, int guess, int &a, int &b)
{
	a = 0, b = 0;
	int ansarr[4];
	int guessarr[4];

	for (int i = 3; i >=0; i--)
	{
		ansarr[i] = ans % 10;
		guessarr[i] = guess % 10;
		ans /= 10;
		guess = guess / 10;
	}

	for (int i = 0; i < 4; i++)
	{
		if (ansarr[i] == guessarr[i])
		{
			a++;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (ansarr[i] == guessarr[j] && i != j)
			{
				b++;
			}
		}
	}

}


int main()
{
	int ans = randomnum();
	int attempt = 0;
	int maxattempt = 10;
	cout << "我已经想好了一个四位数字（每位1-9且不重复），你有" << maxattempt << "次机会来猜它。" << endl;
	int guess;
	while (attempt < maxattempt)
	{
		cout << "第" << attempt + 1 << "次尝试" << endl;
		cout << "请输入你的猜测" << endl;
		cin >> guess;
		if (!input(guess))
		{
			cout << "输入无效，请确保输入一个四位数（每位1-9且不重复）。" << endl;
			continue;
		}
		
		int a, b;
		compare(ans, guess, a, b);
		if (a == 4)
		{
			cout << "恭喜你猜对了。答案是"<<ans << endl;
			break;
		}
		else
		{
			cout << a << "个数字位置与数字均正确" << endl;
			cout << b << "个数字数字正确位置错误" << endl;
			attempt++;
		}

	}
	if (attempt == maxattempt)
	{
		cout << "很遗憾次数用完" << endl;
		cout << "答案是" << ans << endl;
	}
	return 0;
}