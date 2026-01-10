using SFML.Graphics;
using SFML.System;
using SFML.Window;
using System;
using System.Collections.Generic;

public class UiSFMLManager : IUiSFMLManager
{
    private struct Button
    {
        public RectangleShape rect;
        public Text text;
        public int actionId;
        public bool isHovered;
    }

    private RenderWindow window;
    private Font font;
    private GameState currentGameStateRef;

    private const uint WINDOW_WIDTH = 1200;
    private const uint WINDOW_HEIGHT = 600;

    private GameSFMLVersion gameRef = null;

    private bool showInventory = false;
    private bool showSaveLoad = false;
    private bool showDifficulty = false;
    private bool showRestart = false;

    private bool isWaitingForFilename = false;
    private int currentFileAction = 0;
    private string currentFilename = "";
    private Text filenameText;
    private RectangleShape filenameBox;
    private Text filenameLabel;

    private const int MAX_LOG_LINES = 8;

    private Button restartButton;
    private Button exitButton;
    private bool restartButtonCreated = false;

    private List<Button> mainButtons = new List<Button>();
    private List<Button> itemButtons = new List<Button>();
    private List<Button> saveLoadButtons = new List<Button>();
    private List<Button> difficultyButtons = new List<Button>();

    public UiSFMLManager(GameState gameState)
    {
        currentGameStateRef = gameState;

        window = new RenderWindow(new VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ruletka");

        window.Closed += OnWindowClosed;
        window.MouseButtonPressed += OnMouseButtonPressed;
        window.KeyPressed += OnKeyPressed;
        window.TextEntered += OnTextEntered;

        gameRef = null;
        showInventory = false;
        showSaveLoad = false;
        showDifficulty = false;
        showRestart = false;
        isWaitingForFilename = false;
        currentFileAction = 0;
        currentFilename = "";
        restartButtonCreated = false;

        gameState.log = new List<string>(MAX_LOG_LINES);

        font = new Font("arial.ttf");
        if (font == null)
        {
            font = new Font("assets/fonts/arial.ttf");
        }
    }

    private void OnWindowClosed(object sender, EventArgs e)
    {
        window.Close();
        if (gameRef != null)
        {
            gameRef.HandlePlayerChoice((int)GameEnums.Choice.EXIT);
        }
    }

    private void OnMouseButtonPressed(object sender, MouseButtonEventArgs e)
    {
        if (e.Button == Mouse.Button.Left)
        {
            Vector2i mousePos = new Vector2i(e.X, e.Y);

            if (restartButtonCreated)
            {
                Console.WriteLine($"Testing buttons at mouse: {e.X}, {e.Y}");

                if (restartButton.rect.GetGlobalBounds().Contains(mousePos.X, mousePos.Y))
                {
                    Console.WriteLine("RESTART CLICKED!");
                    if (gameRef != null)
                    {
                        gameRef.HandleRestartChoice((int)GameEnums.RestartChoice.RESTART_YES);
                    }
                    return;
                }

                if (exitButton.rect.GetGlobalBounds().Contains(mousePos.X, mousePos.Y))
                {
                    Console.WriteLine("EXIT CLICKED!");
                    if (gameRef != null)
                    {
                        gameRef.HandleRestartChoice((int)GameEnums.RestartChoice.RESTART_NO);
                    }
                    return;
                }
            }
            if (currentGameStateRef != null &&
                currentGameStateRef.currentGameState == GameEnums.GameStateEnum.STATE_RUNNING)
            {
                HandleNormalGameInput(currentGameStateRef, mousePos);
            }
        }
    }

    private void OnKeyPressed(object sender, KeyEventArgs e)
    {
        if (e.Code == Keyboard.Key.Escape)
        {
            if (isWaitingForFilename)
            {
                isWaitingForFilename = false;
                AddToLog(currentGameStateRef, "Anulowano wybor pliku");
            }
            else if (showInventory)
            {
                showInventory = false;
                AddToLog(currentGameStateRef, "Anulowano wybor przedmiotu");
            }
            else if (showSaveLoad)
            {
                showSaveLoad = false;
            }
            else if (showDifficulty)
            {
                showDifficulty = false;
            }
            else if (showRestart)
            {
                showRestart = false;
            }
        }
    }

    private void OnTextEntered(object sender, TextEventArgs e)
    {
        if (isWaitingForFilename)
        {
            char unicodeChar = e.Unicode[0];
            uint unicode = (uint)unicodeChar;

            if (unicode == 8)
            {
                if (!string.IsNullOrEmpty(currentFilename))
                {
                    currentFilename = currentFilename.Substring(0, currentFilename.Length - 1);
                    filenameText.DisplayedString = currentFilename;
                }
            }
            else if (unicode == 13)
            {
                if (string.IsNullOrWhiteSpace(currentFilename))
                {
                    AddToLog(currentGameStateRef, "Nazwa pliku nie może być pusta!");
                    return;
                }

                isWaitingForFilename = false;
                showSaveLoad = false;

                try
                {
                    if (currentFileAction == (int)GameEnums.Choice.SAVE)
                    {
                        AddToLog(currentGameStateRef, "Zapisuję grę jako: " + currentFilename);

                        if (gameRef != null)
                        {
                            try
                            {
                                gameRef.HandleSaveLoadWithFilename((int)GameEnums.Choice.SAVE, currentFilename);
                            }
                            catch
                            {
                                AddToLog(currentGameStateRef, "Błąd: brak metody zapisu w gameRef");
                                Console.WriteLine("DEBUG: Brak metody zapisu w gameRef");
                            }
                        }
                    }
                    else if (currentFileAction == (int)GameEnums.Choice.LOAD)
                    {
                        AddToLog(currentGameStateRef, "Wczytuję grę z: " + currentFilename);

                        if (gameRef != null)
                        {
                            try
                            {
                                gameRef.HandleSaveLoadWithFilename((int)GameEnums.Choice.LOAD, currentFilename);
                            }
                            catch
                            {
                                AddToLog(currentGameStateRef, "Błąd: brak metody wczytywania w gameRef");
                                Console.WriteLine("DEBUG: Brak metody wczytywania w gameRef");
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    AddToLog(currentGameStateRef, "Błąd: " + ex.Message);
                    Console.WriteLine("DEBUG: Błąd zapisu/wczytywania: " + ex.Message);
                }
            }
            else if (unicode >= 32 && unicode < 128)
            {
                if (currentFilename.Length < 50)
                {
                    currentFilename += unicodeChar;
                    filenameText.DisplayedString = currentFilename;
                }
            }
        }
    }

    public bool Initialize()
    {
        window.SetFramerateLimit(60);

        CreateMainButtons();
        CreateItemButtons();
        CreateDifficultyButtons();
        CreateSaveLoadButtons();

        return font != null;
    }

    private void CreateSaveLoadButtons()
    {
        saveLoadButtons.Clear();

        float width = 130;
        float height = 40;

        List<KeyValuePair<string, int>> buttons = new List<KeyValuePair<string, int>>
        {
            new KeyValuePair<string, int>("Zapisz", (int)GameEnums.Choice.SAVE),
            new KeyValuePair<string, int>("Wczytaj", (int)GameEnums.Choice.LOAD),
            new KeyValuePair<string, int>("Anuluj", -1)
        };

        for (int i = 0; i < buttons.Count; i++)
        {
            Button btn = new Button();
            btn.actionId = buttons[i].Value;
            btn.isHovered = false;

            btn.rect = new RectangleShape(new Vector2f(width, height));
            btn.rect.Position = new Vector2f(0, 0);
            btn.rect.FillColor = new Color(70, 70, 70);
            btn.rect.OutlineColor = Color.White;
            btn.rect.OutlineThickness = 1;

            btn.text = new Text(buttons[i].Key, font, 16);
            btn.text.FillColor = Color.White;
            btn.text.Position = new Vector2f(0, 0);

            saveLoadButtons.Add(btn);
        }
    }

    public void DrawStatsPanel(GameState gameState, float x, float y, bool isHuman)
    {
        IPlayer player = isHuman ? gameState.human : gameState.computer;

        string title = isHuman ? "GRACZ" : "KOMPUTER";
        Color color = isHuman ? Color.Green : Color.Red;

        RectangleShape panel = new RectangleShape(new Vector2f(380, 350));
        panel.Position = new Vector2f(x, y);
        panel.FillColor = new Color(40, 40, 40, 220);
        panel.OutlineColor = Color.White;
        panel.OutlineThickness = 2;
        window.Draw(panel);

        Text titleText = new Text(title, font, 28);
        titleText.FillColor = color;
        titleText.Position = new Vector2f(x + 20, y + 20);
        window.Draw(titleText);

        Text hpText = new Text("HP: " + player.GetHP() + "/" +
            gameState.gameConfig.maxPlayerHP, font, 22);
        hpText.FillColor = Color.White;
        hpText.Position = new Vector2f(x + 20, y + 70);
        window.Draw(hpText);

        float hpPercent = (float)player.GetHP() / gameState.gameConfig.maxPlayerHP;
        RectangleShape hpBarBg = new RectangleShape(new Vector2f(340, 20));
        hpBarBg.Position = new Vector2f(x + 20, y + 110);
        hpBarBg.FillColor = new Color(50, 50, 50);
        window.Draw(hpBarBg);

        RectangleShape hpBar = new RectangleShape(new Vector2f(340 * hpPercent, 20));
        hpBar.Position = new Vector2f(x + 20, y + 110);
        hpBar.FillColor = color;
        window.Draw(hpBar);

        float itemY = y + 150;
        List<KeyValuePair<string, int>> items = new List<KeyValuePair<string, int>>
        {
            new KeyValuePair<string, int>("Pily:", player.GetSaws()),
            new KeyValuePair<string, int>("Piwa:", player.GetBeers()),
            new KeyValuePair<string, int>("Lupy:", player.GetMagnifiers()),
            new KeyValuePair<string, int>("Telefony:", player.GetCellPhones()),
            new KeyValuePair<string, int>("Kajdanki:", player.GetHandCuffs()),
            new KeyValuePair<string, int>("Inwertery:", player.GetInverters())
        };

        List<string> icons = new List<string> { "[P]", "[B]", "[L]", "[T]", "[K]", "[I]" };

        for (int i = 0; i < items.Count; i++)
        {
            Text itemText = new Text(icons[i] + " " + items[i].Key + " " +
                items[i].Value, font, 18);
            itemText.FillColor = Color.White;
            itemText.Position = new Vector2f(x + 20, itemY);
            window.Draw(itemText);
            itemY += 32;
        }
    }

    public void DrawMagazinePanel(GameState gameState, float x, float y)
    {
        RectangleShape panel = new RectangleShape(new Vector2f((WINDOW_WIDTH - 40) / 2, 100));
        panel.Position = new Vector2f(x, y);
        panel.FillColor = new Color(50, 30, 30, 220);
        panel.OutlineColor = Color.White;
        panel.OutlineThickness = 2.0f;
        window.Draw(panel);

        Text title = new Text("MAGAZYNEK", font, 20);
        title.FillColor = Color.Yellow;
        title.Position = new Vector2f(x + 15, y + 15);
        window.Draw(title);

        int full = gameState.magazine.ShowFull();
        int empty = gameState.magazine.ShowEmpty();
        int total = gameState.magazine.ShowBulletCount();

        string statsText;
        if (!gameState.wasMagazineShown)
        {
            statsText = "Pelne: " + full + "   Puste: " + empty + "   Razem: " + total;
        }
        else
        {
            string mark = "?";
            statsText = "Pelne: " + mark + "   Puste: " + mark + "   Razem: " + total;
        }

        Text stats = new Text(statsText, font, 18);
        stats.FillColor = Color.White;
        stats.Position = new Vector2f(x + 15, y + 55);
        window.Draw(stats);
    }

    public void DrawDifficultyInfoPanel(GameState gameState, float x, float y)
    {
        RectangleShape panel = new RectangleShape(new Vector2f((WINDOW_WIDTH - 40) / 2, 100));
        panel.Position = new Vector2f(x, y);
        panel.FillColor = new Color(30, 30, 50, 220);
        panel.OutlineColor = Color.White;
        panel.OutlineThickness = 2.0f;
        window.Draw(panel);

        Text title = new Text("POZIOM TRUDNOSCI", font, 20);
        title.FillColor = Color.Magenta;
        title.Position = new Vector2f(x + 15, y + 15);
        window.Draw(title);

        string difficultyText;
        switch (gameState.ai.GetDifficulty())
        {
            case (int)GameEnums.Difficulty.EASY: difficultyText = "LATWY"; break;
            case (int)GameEnums.Difficulty.NORMAL: difficultyText = "NORMALNY"; break;
            case (int)GameEnums.Difficulty.HARD: difficultyText = "TRUDNY"; break;
            default: difficultyText = "NIEUSTAWIONO"; break;
        }

        Text difficultyDisplay = new Text(difficultyText, font, 22);
        difficultyDisplay.FillColor = Color.Cyan;
        difficultyDisplay.Position = new Vector2f(x + 15, y + 55);
        window.Draw(difficultyDisplay);
    }

    public void DrawGameLog(GameState gameState, float x, float y)
    {
        RectangleShape panel = new RectangleShape(new Vector2f(380, 350));
        panel.Position = new Vector2f(x, y);
        panel.FillColor = new Color(30, 30, 30, 220);
        panel.OutlineColor = Color.White;
        panel.OutlineThickness = 2;
        window.Draw(panel);

        Text title = new Text("LOG GRY", font, 22);
        title.Position = new Vector2f(x + 20, y + 15);
        title.FillColor = Color.Green;
        window.Draw(title);

        float textY = y + 55;
        foreach (var line in gameState.log)
        {
            Text logText = new Text(line, font, 18);
            logText.FillColor = Color.White;
            logText.Position = new Vector2f(x + 20, textY);
            window.Draw(logText);
            textY += 30;
        }
    }

    public void DrawWaitForComputerPanel(float x, float y)
    {
        RectangleShape panel = new RectangleShape(new Vector2f(WINDOW_WIDTH - 40, 80));
        panel.Position = new Vector2f(x, y);
        panel.FillColor = new Color(50, 50, 70, 220);
        panel.OutlineColor = Color.Red;
        panel.OutlineThickness = 2.0f;
        window.Draw(panel);

        Text waitText = new Text("TRWA TURA KOMPUTERA...", font, 28);
        FloatRect bounds = waitText.GetLocalBounds();
        waitText.Origin = new Vector2f(bounds.Width / 2, bounds.Height / 2);
        waitText.Position = new Vector2f(WINDOW_WIDTH / 2, y + 40);
        waitText.FillColor = Color.Yellow;
        window.Draw(waitText);
    }

    public void DrawGameOverScreen(GameState gameState, float x, float y)
    {
        RectangleShape panel = new RectangleShape(new Vector2f(600, 400));
        panel.Position = new Vector2f(x, y);
        panel.FillColor = new Color(30, 30, 50, 230);
        panel.OutlineColor = Color.Yellow;
        panel.OutlineThickness = 3.0f;
        window.Draw(panel);

        Text gameOverText = new Text("KONIEC GRY", font, 48);
        gameOverText.FillColor = Color.Red;
        gameOverText.Style = Text.Styles.Bold;
        FloatRect bounds = gameOverText.GetLocalBounds();
        gameOverText.Origin = new Vector2f(bounds.Width / 2, bounds.Height / 2);
        gameOverText.Position = new Vector2f(x + 300, y + 70);
        window.Draw(gameOverText);

        string winnerText;
        Color winnerColor;
        if (gameState.currentGameState == GameEnums.GameStateEnum.STATE_HUMAN_WIN)
        {
            winnerText = "GRACZ WYGRYWA!";
            winnerColor = Color.Green;
        }
        else
        {
            winnerText = "KOMPUTER WYGRYWA!";
            winnerColor = Color.Red;
        }

        Text winnerDisplay = new Text(winnerText, font, 36);
        winnerDisplay.FillColor = winnerColor;
        winnerDisplay.Style = Text.Styles.Bold;
        bounds = winnerDisplay.GetLocalBounds();
        winnerDisplay.Origin = new Vector2f(bounds.Width / 2, bounds.Height / 2);
        winnerDisplay.Position = new Vector2f(x + 300, y + 150);
        window.Draw(winnerDisplay);

        string stats = "Gracz: " + gameState.human.GetHP() + " HP | Komputer: " + gameState.computer.GetHP() + " HP";
        Text statsText = new Text(stats, font, 22);
        statsText.FillColor = Color.White;
        statsText.Position = new Vector2f(x + 180, y + 210);
        window.Draw(statsText);

        if (!restartButtonCreated)
        {
            CreateRestartButtons(x, y);
        }

        window.Draw(restartButton.rect);
        window.Draw(restartButton.text);
        window.Draw(exitButton.rect);
        window.Draw(exitButton.text);
    }

    public void DrawFilenameInput(float x, float y)
    {
        RectangleShape overlay = new RectangleShape(new Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        overlay.FillColor = new Color(0, 0, 0, 200);
        window.Draw(overlay);

        if (filenameLabel == null)
        {
            filenameLabel = new Text("", font, 20);
            filenameLabel.FillColor = Color.White;
            filenameLabel.Position = new Vector2f(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 40);
        }

        if (currentFileAction == (int)GameEnums.Choice.SAVE)
        {
            filenameLabel.DisplayedString = "ZAPIS GRY - Podaj nazwe pliku:";
            filenameLabel.FillColor = Color.Green;
        }
        else if (currentFileAction == (int)GameEnums.Choice.LOAD)
        {
            filenameLabel.DisplayedString = "WCZYTYWANIE GRY - Podaj nazwe pliku:";
            filenameLabel.FillColor = Color.Yellow;
        }

        window.Draw(filenameBox);
        window.Draw(filenameText);
        window.Draw(filenameLabel);

        Text instruction = new Text("Wpisz nazwe i nacisnij Enter (Esc - anuluj)", font, 18);
        instruction.FillColor = Color.White;
        instruction.Position = new Vector2f(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 + 60);
        window.Draw(instruction);
    }

    public void DrawDecisionPanel(GameState gameState, float x, float y)
    {
        RectangleShape panel = new RectangleShape(new Vector2f(WINDOW_WIDTH - 20, 50));
        panel.Position = new Vector2f(x, y);
        panel.FillColor = new Color(50, 50, 50, 220);
        panel.OutlineColor = Color.White;
        panel.OutlineThickness = 2;
        window.Draw(panel);

        var buttons = showInventory ? itemButtons : showDifficulty ? difficultyButtons : mainButtons;

        float totalButtonsWidth = 0;
        foreach (var btn in buttons)
        {
            totalButtonsWidth += btn.rect.Size.X;
        }
        totalButtonsWidth += (buttons.Count - 1) * 8;

        float startX = x + (panel.Size.X - totalButtonsWidth) / 2;
        float currentX = startX;

        for (int i = 0; i < buttons.Count; i++)
        {
            Button btn = buttons[i];
            btn.rect.Position = new Vector2f(currentX, y + 5);

            window.Draw(btn.rect);

            FloatRect bounds = btn.text.GetLocalBounds();
            btn.text.Origin = new Vector2f(bounds.Width / 2, bounds.Height / 2);
            btn.text.Position = new Vector2f(currentX + btn.rect.Size.X / 2, y + 5 + btn.rect.Size.Y / 2);

            window.Draw(btn.text);

            currentX += btn.rect.Size.X + 8;
        }
    }

    public void CreateMainButtons()
    {
        mainButtons.Clear();

        float width = 130;
        float height = 40;

        List<KeyValuePair<string, int>> buttons = new List<KeyValuePair<string, int>>
        {
            new KeyValuePair<string, int>("Regen", (int)GameEnums.Choice.HEAL),
            new KeyValuePair<string, int>("Strzel", (int)GameEnums.Choice.SHOOT),
            new KeyValuePair<string, int>("Przedmiot", (int)GameEnums.Choice.USEITEM),
            new KeyValuePair<string, int>("Zapisz", (int)GameEnums.Choice.SAVE),
            new KeyValuePair<string, int>("Wczytaj", (int)GameEnums.Choice.LOAD),
            new KeyValuePair<string, int>("Trudnosc", (int)GameEnums.Choice.DIFFICULTY),
            new KeyValuePair<string, int>("Wyjdz", (int)GameEnums.Choice.EXIT)
        };

        for (int i = 0; i < buttons.Count; i++)
        {
            Button btn = new Button();
            btn.actionId = buttons[i].Value;
            btn.isHovered = false;

            btn.rect = new RectangleShape(new Vector2f(width, height));
            btn.rect.Position = new Vector2f(0, 0);
            btn.rect.FillColor = new Color(70, 70, 70);
            btn.rect.OutlineColor = Color.White;
            btn.rect.OutlineThickness = 1;

            btn.text = new Text(buttons[i].Key, font, 16);
            btn.text.FillColor = Color.White;
            btn.text.Position = new Vector2f(0, 0);

            mainButtons.Add(btn);
        }
    }

    public void CreateItemButtons()
    {
        itemButtons.Clear();

        float width = 130;
        float height = 40;

        List<KeyValuePair<string, int>> items = new List<KeyValuePair<string, int>>
        {
            new KeyValuePair<string, int>("Kajdanki", (int)GameEnums.Item.HANDCUFFS),
            new KeyValuePair<string, int>("Piwo", (int)GameEnums.Item.BEER),
            new KeyValuePair<string, int>("Lupa", (int)GameEnums.Item.MAGNIFIER),
            new KeyValuePair<string, int>("Pila", (int)GameEnums.Item.SAW),
            new KeyValuePair<string, int>("Telefon", (int)GameEnums.Item.CELLPHONE),
            new KeyValuePair<string, int>("Inwerter", (int)GameEnums.Item.INVERTER)
        };

        for (int i = 0; i < items.Count; i++)
        {
            Button btn = new Button();
            btn.actionId = items[i].Value;
            btn.isHovered = false;

            btn.rect = new RectangleShape(new Vector2f(width, height));
            btn.rect.Position = new Vector2f(0, 0);
            btn.rect.FillColor = new Color(70, 70, 70);
            btn.rect.OutlineColor = Color.White;
            btn.rect.OutlineThickness = 1;

            btn.text = new Text(items[i].Key, font, 16);
            btn.text.FillColor = Color.White;
            btn.text.Position = new Vector2f(0, 0);

            itemButtons.Add(btn);
        }
    }

    public void CreateDifficultyButtons()
    {
        difficultyButtons.Clear();

        float totalWidth = 3 * 130 + 2 * 8;
        float startX = (WINDOW_WIDTH - totalWidth) / 2;
        float y = 730;
        float width = 130;
        float height = 40;
        float spacing = 8;

        List<KeyValuePair<string, int>> buttons = new List<KeyValuePair<string, int>>
        {
            new KeyValuePair<string, int>("Latwy", (int)GameEnums.Difficulty.EASY),
            new KeyValuePair<string, int>("Normalny", (int)GameEnums.Difficulty.NORMAL),
            new KeyValuePair<string, int>("Trudny", (int)GameEnums.Difficulty.HARD),
        };

        for (int i = 0; i < buttons.Count; i++)
        {
            Button btn = new Button();
            btn.actionId = buttons[i].Value;
            btn.isHovered = false;

            float btnX = startX + (i * (width + spacing));
            btn.rect = new RectangleShape(new Vector2f(width, height));
            btn.rect.Position = new Vector2f(btnX, y);
            btn.rect.FillColor = new Color(70, 70, 90);
            btn.rect.OutlineColor = Color.Magenta;
            btn.rect.OutlineThickness = 1;

            btn.text = new Text(buttons[i].Key, font, 16);
            btn.text.FillColor = Color.White;

            FloatRect bounds = btn.text.GetLocalBounds();
            btn.text.Origin = new Vector2f(bounds.Width / 2, bounds.Height / 2);
            btn.text.Position = new Vector2f(btnX + width / 2, y + height / 2);

            difficultyButtons.Add(btn);
        }
    }

    public void CreateRestartButtons(float x, float y)
    {
        restartButton.rect = new RectangleShape(new Vector2f(200, 60));
        restartButton.rect.Position = new Vector2f(x + 50, y + 250);
        restartButton.rect.FillColor = new Color(70, 120, 70);
        restartButton.rect.OutlineColor = Color.White;
        restartButton.rect.OutlineThickness = 2;

        restartButton.text = new Text("ZAGRAJ PONOWNIE", font, 20);
        restartButton.text.FillColor = Color.White;
        restartButton.actionId = (int)GameEnums.RestartChoice.RESTART_YES;
        restartButton.isHovered = false;

        FloatRect bounds = restartButton.text.GetLocalBounds();
        restartButton.text.Origin = new Vector2f(bounds.Width / 2, bounds.Height / 2);
        restartButton.text.Position = new Vector2f(x + 150, y + 280);

        exitButton.rect = new RectangleShape(new Vector2f(200, 60));
        exitButton.rect.Position = new Vector2f(x + 350, y + 250);
        exitButton.rect.FillColor = new Color(120, 70, 70);
        exitButton.rect.OutlineColor = Color.White;
        exitButton.rect.OutlineThickness = 2;

        exitButton.text = new Text("WYJSCIE", font, 20);
        exitButton.text.FillColor = Color.White;
        exitButton.actionId = (int)GameEnums.RestartChoice.RESTART_NO;
        exitButton.isHovered = false;

        bounds = exitButton.text.GetLocalBounds();
        exitButton.text.Origin = new Vector2f(bounds.Width / 2, bounds.Height / 2);
        exitButton.text.Position = new Vector2f(x + 450, y + 280);

        restartButtonCreated = true;
    }

    public void StartFilenameInput(int action)
    {
        isWaitingForFilename = true;
        currentFileAction = action;
        showSaveLoad = false;

        if (filenameLabel == null)
        {
            filenameLabel = new Text("", font, 20);
            filenameLabel.FillColor = Color.White;
            filenameLabel.Position = new Vector2f(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 40);
        }

        if (action == (int)GameEnums.Choice.SAVE)
        {
            currentFilename = "save";
            filenameLabel.DisplayedString = "Podaj nazwe pliku do ZAPISU:";
        }
        else if (action == (int)GameEnums.Choice.LOAD)
        {
            currentFilename = "save";
            filenameLabel.DisplayedString = "Podaj nazwe pliku do WCZYTANIA:";
        }

        filenameBox = new RectangleShape(new Vector2f(400, 40));
        filenameBox.Position = new Vector2f(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2);
        filenameBox.FillColor = new Color(50, 50, 70);
        filenameBox.OutlineColor = Color.Cyan;
        filenameBox.OutlineThickness = 2;

        filenameText = new Text(currentFilename, font, 24);
        filenameText.FillColor = Color.White;
        filenameText.Position = new Vector2f(WINDOW_WIDTH / 2 - 190, WINDOW_HEIGHT / 2 + 5);

        filenameLabel = new Text("", font, 20);
        filenameLabel.FillColor = Color.White;
        filenameLabel.Position = new Vector2f(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 40);
    }

    public void HandleFilenameInput(GameState gameState, Event sfmlEvent)
    {
    }

    public void HandleGameOverInput(GameState gameState, Vector2i mousePos)
    {
        if (restartButtonCreated)
        {
            if (restartButton.rect.GetGlobalBounds().Contains(mousePos.X, mousePos.Y))
            {
                if (gameRef != null)
                {
                    gameRef.HandleRestartChoice((int)GameEnums.RestartChoice.RESTART_YES);
                    gameState.waitingForRestartChoice = false;
                    gameState.currentGameState = GameEnums.GameStateEnum.STATE_RUNNING;
                }
                AddToLog(gameState, "Wybrano: Zagraj ponownie");
                return;
            }
            else if (exitButton.rect.GetGlobalBounds().Contains(mousePos.X, mousePos.Y))
            {
                if (gameRef != null)
                {
                    gameRef.HandleRestartChoice((int)GameEnums.RestartChoice.RESTART_NO);
                }
                AddToLog(gameState, "Wybrano: Wyjscie");
                return;
            }
        }
    }

    public void HandleNormalGameInput(GameState gameState, Vector2i mousePos)
    {
        if (showInventory)
        {
            foreach (var btn in itemButtons)
            {
                if (btn.rect.GetGlobalBounds().Contains(mousePos.X, mousePos.Y))
                {
                    Console.WriteLine("DEBUG: Kliknieto przedmiot: " + btn.actionId);
                    if (gameRef != null)
                    {
                        gameRef.HandleItemChoice(btn.actionId);
                    }
                    showInventory = false;
                    return;
                }
            }
        }

        if (showSaveLoad)
        {
            foreach (var btn in saveLoadButtons)
            {
                if (btn.rect.GetGlobalBounds().Contains(mousePos.X, mousePos.Y))
                {
                    Console.WriteLine("DEBUG: Kliknieto save/load: " + btn.actionId);
                    StartFilenameInput(btn.actionId);
                    return;
                }
            }
        }

        if (showDifficulty)
        {
            foreach (var btn in difficultyButtons)
            {
                if (btn.rect.GetGlobalBounds().Contains(mousePos.X, mousePos.Y))
                {
                    Console.WriteLine("DEBUG: Kliknieto trudnosc: " + btn.actionId);
                    if (gameRef != null)
                    {
                        gameRef.HandleDifficultyChoice(btn.actionId);
                    }
                    showDifficulty = false;
                    return;
                }
            }
        }

        foreach (var btn in mainButtons)
        {
            if (btn.rect.GetGlobalBounds().Contains(mousePos.X, mousePos.Y))
            {
                Console.WriteLine("DEBUG: Kliknieto przycisk: " + btn.actionId);

                if (gameRef != null)
                {
                    gameRef.HandlePlayerChoice(btn.actionId);
                }

                if (btn.actionId == (int)GameEnums.Choice.USEITEM)
                {
                    showInventory = true;
                }
                else if (btn.actionId == (int)GameEnums.Choice.SAVE || btn.actionId == (int)GameEnums.Choice.LOAD)
                {
                    showSaveLoad = true;
                }
                else if (btn.actionId == (int)GameEnums.Choice.DIFFICULTY)
                {
                    showDifficulty = true;
                }
                else if (btn.actionId == (int)GameEnums.RestartChoice.RESTART_YES ||
                         btn.actionId == (int)GameEnums.RestartChoice.RESTART_NO)
                {
                    showRestart = false;
                }

                return;
            }
        }
    }

    public void ProcessEvents(GameState gameState)
    {
        window.DispatchEvents();
    }

    public void Render(GameState gameState)
    {
        window.Clear(new Color(20, 20, 30));

        DrawMagazinePanel(gameState, 10, 20);

        DrawDifficultyInfoPanel(gameState, WINDOW_WIDTH / 2 + 10, 20);

        float panelWidth = 380;
        float spacing = 20;
        float totalWidth = 3 * panelWidth + 2 * spacing;
        float startX = (WINDOW_WIDTH - totalWidth) / 2;

        DrawStatsPanel(gameState, startX, 140, true);

        DrawGameLog(gameState, startX + panelWidth + spacing, 140);

        DrawStatsPanel(gameState, startX + 2 * (panelWidth + spacing), 140, false);

        if (gameState.currentGameState == GameEnums.GameStateEnum.STATE_HUMAN_WIN ||
            gameState.currentGameState == GameEnums.GameStateEnum.STATE_COMPUTER_WIN)
        {
            DrawGameOverScreen(gameState, (WINDOW_WIDTH - (WINDOW_WIDTH / 2)) / 2, WINDOW_HEIGHT / 6);
        }
        else
        {
            if (isWaitingForFilename)
            {
                DrawFilenameInput(0, 0);
            }
            else if (showInventory)
            {
                DrawDecisionPanel(gameState, 10, 510);
            }
            else if (showRestart)
            {
                DrawGameOverScreen(gameState, (WINDOW_WIDTH - (WINDOW_WIDTH / 2)) / 2, WINDOW_HEIGHT / 6);
            }
            else
            {
                DrawDecisionPanel(gameState, 10, 510);
            }
        }

        window.Display();
    }

    public void AddToLog(GameState gameState, string message)
    {
        gameState.log.Add(message);
        if (gameState.log.Count > MAX_LOG_LINES)
        {
            gameState.log.RemoveAt(0);
        }
    }

    public void ClearLog(GameState gameState)
    {
        gameState.log.Clear();
    }

    public bool IsWindowOpen()
    {
        return window.IsOpen;
    }

    public void CloseWindow()
    {
        if (window.IsOpen)
        {
            window.Close();
        }
    }

    public void SetGameReference(GameSFMLVersion game)
    {
        gameRef = game;
    }

    public void ResetUI(GameState gameState)
    {
        showInventory = false;
        showSaveLoad = false;
        showDifficulty = false;
        showRestart = false;
        isWaitingForFilename = false;
        restartButtonCreated = false;
        ClearLog(gameState);
    }

    public void ShowMessage(GameState gameState, string message)
    {
        AddToLog(gameState, message);
    }

    public void DisplayStats(GameState gameState)
    {
        Console.WriteLine("Gracz: " + gameState.human.GetHP() + " HP, Komputer: " + gameState.computer.GetHP() + " HP");
    }

    public uint GetWindowWidth() { return WINDOW_WIDTH; }
    public uint GetWindowHeight() { return WINDOW_HEIGHT; }

    public bool IsShowingItemMenu() { return showInventory; }
    public bool IsShowingSaveLoadMenu() { return showSaveLoad; }
    public bool IsShowingDifficultyMenu() { return showDifficulty; }
    public bool IsRestartButtonCreated() { return restartButtonCreated; }

    public void ShowItemMenu(bool show) { showInventory = show; }
    public void ShowSaveLoadMenu(bool show) { showSaveLoad = show; }
    public void ShowDifficultyMenu(bool show) { showDifficulty = show; }
    public void ShowRestartMenu(bool show) { showRestart = show; }
}