#pragma once
/*
* �Ǵн� �̱���
* 1. ���� ��ü�� �Ҹ�Ǹ� �Ҹ��ڿ� ���ؼ� bDestroyed ������ true�� �Ǹ鼭
* ���� �Ҹ� ������ �˷��ش�.
* 
* 2. �Ҹ� �� GetInstance() �Լ��� ���ؼ� �� ȣ���, bDestroyed = false�� �ٲ��ָ鼭
* ������ ���� �ʾҴٰ� �˷���
* 
* - �� ������ �� replacement new �� �̿��Ͽ� �ش� ��ü�� �����ڸ� �� ȣ���ؼ� ����ؼ� �ǻ츮�� �ý���
* 
* �����Ϸ��� ���� ��ü �Ҹ� �� �ش� �޸𸮸� �ʱ�ȭ ���� �ʱ� ������ �޸𸮸� �����Ͽ� 
* ��ü�� �����ڸ� �� ȣ���ϸ� ��ü�� ���� �� �� �ֱ� �����̴�.
* �� �� atexit() �Լ��� KillPhoenix() �� �ݹ����� ����� �߱� ������ ���α׷� ����ÿ� 
* Phoenix Singleton ��ü�� �Ҹ��ڸ� �̿��� ���ҽ� ������ �� �� �ְ� �ȴ�.
*/
class UI
{
private:
	static bool bDestroyed;
	static UI* uIns;

	UI() {}
	~UI() { bDestroyed = true; }

	static void Create();
	static void KillUI();

public:
	static UI* GetInstance();

	int SelectMenu();
	void ShowLogo() const;
	void ShowHowToPlay() const;
	void ShowGameWin() const;
	void ShowGameOver() const;
};

