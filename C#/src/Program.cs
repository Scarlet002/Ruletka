using System;
using System.Runtime.InteropServices;

class Program
{
    [DllImport("kernel32.dll")]
    static extern IntPtr GetConsoleWindow();

    [DllImport("user32.dll")]
    static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);

    static void Main()
    {
        Random rand = new Random(Environment.TickCount);

        SaveTXTManager saverTXT = new SaveTXTManager();
        LoadTXTManager loaderTXT = new LoadTXTManager();
        SaveJSONManager saverJSON = new SaveJSONManager();
        LoadJSONManager loaderJSON = new LoadJSONManager();

        try
        {
            //GameConsoleVersion game = new GameConsoleVersion(loaderJSON, saverJSON);
            //game.StartGame();

            GameSFMLVersion game = new GameSFMLVersion(loaderJSON, saverJSON);
            game.Run();
        }
        catch (Exception e)
        {
            Console.WriteLine("Gra zostanie zamknieta.");
            Console.WriteLine("Powod: " + e.Message);

            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
            {
                Console.WriteLine("Nacisnij dowolny klawisz, aby kontynuowac...");
                Console.ReadKey();
            }

            Environment.Exit(1);
        }

        Environment.Exit(0);
    }
}