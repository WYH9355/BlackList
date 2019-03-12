#include "Sys.h"

//构造		
Sys::Sys()
{
	if ( nullptr == _rootprocess )
	{
		_rootprocess = new RootProcess();
	}
}

//析构
Sys::~Sys()
{
	if ( _rootprocess )
		delete _rootprocess;
}

//界面清单
void Sys::put()
{
	printf("**************************************\n");
	printf("***           欢迎使用            ****\n");
	printf("***        1.Login                ****\n");
	printf("***        2.Register             ****\n");
	printf("***        3.Exit                 ****\n");
	printf("***                               ****\n");
	printf("**************************************\n");
}

//界面运行
void Sys::run()
{
	while ( 1 )
	{
		int n;

		put();
		printf("Input selection：");
		std::cin>>n;
		switch( n )
		{
			case 1:
				CheckLogin();
				break;
			case 2:
				CheckRegister();
				break;
			case 3:
				ExitSys();
				break;
			default:
				std::cout<<"Input error"<<std::endl;
				break;
		}
	}
}

//登录
bool Sys::Login()
{
	bool flag = false;		//登录成功失败

	std::string		name;	//接收键盘账号
	std::string		pw;		//接收键盘密码
	Json::Value		sval;	//发送包
	Json::Reader	read;	//读取
	Json::Value		rval;	//接收包
	std::string		buff;	//接收缓冲区
	struct termios	ts;		//终端属性

	std::cout<<"account：";
	std::cin>>name;

	//密码不回显
	DeleteShow(ts);
	std::cout<<"passwd：";
	std::cin>>pw;
	AddShow(ts);


	//Json打包
	sval[TYPE] = SELECT;//查询操作
	sval[FD]   = HOSTFD;
	sval[NAME] = name.c_str();
	sval[PW]   = pw.c_str();

	//向服务器发送数据
	Server::getServer()->sendServer(sval.toStyledString());

	//接收验证数据
	Server::getServer()->recvServer(buff);
	
	//解析数据
	if ( !read.parse(buff,rval) )
	{
		std::cerr<<"json prase fail;errno:"<<errno<<std::endl;
		return flag;
	}

	//数据非YES 比较正确返回0
	if ( 0 != rval[REASON].asString().compare(YES) )
	{
		return flag;
	}

	flag = true;
	return flag;
}

//检查登录
void Sys::CheckLogin()
{
	bool tag = false;
	char ch;
	do
	{
		tag = Login();
		if ( !tag )
		{
			std::cout<<"\nLogon failure account or password error!\n"
				<<std::endl;
			std::cout<<"继续登录？y/n：";
			std::cin>>ch;
		}
	}while(tag == false && ch == 'y');
	if( tag )
	{
		std::cout<<"\nLogin successfully\n"<<std::endl;

		_rootprocess->run();
	}
}

//注册
bool Sys::Register()
{
	bool flag = false;		//注册成功失败

	std::string		name;	//接收键盘账号
	std::string		pw;		//接收键盘密码
	Json::Value		sval;	//发送包
	Json::Reader	read;	//读取操作
	Json::Value		rval;	//接收包
	std::string		buff;	//接收缓冲区
	struct termios	ts;		//终端属性

	std::cout<<"account：";
	getline(std::cin,name);

	//密码不回显
	DeleteShow(ts);
	std::cout<<"passwd：";
	getline(std::cin,pw);
	std::cout<<std::endl;
	AddShow(ts);

	//Json打包
	sval[TYPE] = INSERT;//增加操作
	sval[FD]   = HOSTFD;
	sval[NAME] = name.c_str();
	sval[PW]   = pw.c_str();

	//向服务器发送数据
	Server::getServer()->sendServer(sval.toStyledString());

	//接收验证数据
	Server::getServer()->recvServer(buff);
	
	//解析数据
	if ( !read.parse(buff,rval) )
	{
		std::cerr<<"json prase fail;errno:"<<errno<<std::endl;
		return flag;
	}

	//数据非YES
	if ( 0 != rval[REASON].asString().compare(YES) )
	{
		return flag;
	}
	flag = true;
	return flag;
}
//检查注册
void Sys::CheckRegister()
{
	bool tag = false;
	char ch;
	do
	{
		tag = Register();
		if ( !tag )
		{
			std::cout<<"\nRegister Account Repetition!\n"
				<<std::endl;
			std::cout<<"继续注册？y/n：";
			std::cin>>ch;
		}
	}while(tag == false && ch == 'y');
	if( tag )
	{
		std::cout<<"\nRegister successfully\n"<<std::endl;
	}
}

//退出
void Sys::ExitSys()
{
	exit(0);
}

//移除回显
void Sys::DeleteShow(struct termios &ts)
{
	struct termios newts;	//终端属性
	tcgetattr(0,&ts);			//获取终端属性
	newts = ts;
	newts.c_lflag &= ~(ECHO|ICANON);//本地属性，回显 ,标准模式(去掉)
	tcsetattr(0,TCSANOW,&newts);//设置新属性
}

//增加回显
void Sys::AddShow(struct termios &ts)
{
	tcsetattr(0,TCSANOW,&ts);//还原终端属性
}


