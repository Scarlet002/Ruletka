using System;
using System.IO;

public class SaveConfig
{
    public static string GetSaveDirectory()
    {
        return "data/saves";
    }

    public static string GetAutoSaveDirectory()
    {
        return "data/saves/autosaves";
    }

    public static bool CreateDirectoryIfNotExists(string path)
    {
        try
        {
            if (!Directory.Exists(path))
            {
                Directory.CreateDirectory(path);
                return true;
            }
            return true;
        }
        catch (Exception e)
        {
            Console.WriteLine("Blad tworzenia katalogu " + path + ": " + e.Message);
            return false;
        }
    }
}