class Command
{
protected:
    typedef void (* func_t)(void);
    Command( ... );

private:
    func_t func;
};

class File : public Command
{
public:
    File(void);
    File( string& _src );
    File( string& _src, string& _dst );

    void Print(void);
    void Copy(void);
    void ShowDir(void);

private:
    string src, dst;
};

class Menu
{
public:
    Menu( Command* _pCommand = NULL );
    ~Menu(void);

    void SetCommand( Command* _pCommand );
    void Run(void);

private:
    Command* pCommand;
};
