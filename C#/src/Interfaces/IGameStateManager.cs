public interface IGameStateManager
{
    void SetItem(int newItem);
    void SetStarter(int newStarter);
    void SetChoice(int newChoice);
    void SetTarget(int newTarget);
    void SetShooter(int newShooter);
    void SetDamage(int newDamage);
    void SetStateOfHandCuffs(bool newState);
    void SetLogLine(string newLogLine);
    int GetStarter();
    int GetChoice();
    int GetTarget();
    int GetShooter();
    int GetDamage();
    int GetItem();
    bool GetStateOfHandCuffs();
    string GetLogLine();
    int RandomizeStarter();
    void ResetDamage();
}