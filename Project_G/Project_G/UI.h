#pragma once
/*
* 피닉스 싱글톤
* 1. 정적 개체가 소멸되면 소멸자에 의해서 bDestroyed 변수가 true가 되면서
* 현재 소멸 정보를 알려준다.
* 
* 2. 소멸 후 GetInstance() 함수를 통해서 재 호출시, bDestroyed = false로 바꿔주면서
* 삭제가 되지 않았다고 알려줌
* 
* - 즉 참조할 때 replacement new 를 이용하여 해당 객체의 생성자를 재 호출해서 계속해서 되살리는 시스템
* 
* 컴파일러는 전역 객체 소멸 시 해당 메모리를 초기화 하지 않기 때문에 메모리를 재사용하여 
* 객체의 생성자만 재 호출하면 객체를 재사용 할 수 있기 때문이다.
* 그 후 atexit() 함수에 KillPhoenix() 를 콜백으로 등록을 했기 때문에 프로그램 종료시에 
* Phoenix Singleton 객체의 소멸자를 이용해 리소스 해제를 할 수 있게 된다.
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

