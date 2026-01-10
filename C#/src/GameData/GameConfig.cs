public struct GameConfig
{
    public GameConfig()
    {
        defaultDamage = 1;
        sawDamage = 2;
        maxPlayerHP = 5;
        maxBullets = 7;
        minBullets = 2;
        maxItemsRand = 1;
        minItemsRand = 1;
        minSaws = 0;
        minBeers = 0;
        minHandCuffs = 0;
        minCellPhones = 0;
        minInverters = 0;
        minMagnifiers = 0;
        minNumberOfItems = 0;
        maxInventorySize = 5;
        numberOfItemTypes = 6;
        numberOfBulletTypes = 2;
        numberOfPlayers = 2;
        minBulletsCount = 0;
        maxLogsInLine = 3;
        defaultDifficulty = GameEnums.Difficulty.NORMAL;
        StarterPlayerHP = maxPlayerHP;
    }

    public int defaultDamage;
    public int sawDamage;
    public int maxPlayerHP;
    public int maxBullets;
    public int minBullets;
    public int maxItemsRand;
    public int minItemsRand;
    public int minSaws;
    public int minBeers;
    public int minHandCuffs;
    public int minCellPhones;
    public int minInverters;
    public int minMagnifiers;
    public int minNumberOfItems;
    public int maxInventorySize;
    public int numberOfItemTypes;
    public int numberOfBulletTypes;
    public int numberOfPlayers;
    public int minBulletsCount;
    public int maxLogsInLine;
    public GameEnums.Difficulty defaultDifficulty;
    public int StarterPlayerHP;
}