using System;
using System.Text.RegularExpressions;

public static class InputValidatorManager
{
    public static bool IsValidFileName(string fileName)
    {
        Regex pattern = new Regex("^[a-zA-Z0-9_-]{1,30}$");
        return pattern.IsMatch(fileName);
    }

    public static bool IsValidMenuChoice(string input)
    {
        Regex pattern = new Regex("^[0-6]$");
        return pattern.IsMatch(input);
    }

    public static bool IsValidItemChoice(string input)
    {
        Regex pattern = new Regex("^[0-6]$");
        return pattern.IsMatch(input);
    }

    public static bool IsValidYesNo(string input)
    {
        Regex pattern = new Regex("^[tTnN]$");
        return pattern.IsMatch(input);
    }

    public static bool IsValidDifficultyChoice(string input)
    {
        Regex pattern = new Regex("^[0-2]$");
        return pattern.IsMatch(input);
    }

    public static string GetValidatedInput(string prompt, Func<string, bool> validator)
    {
        string input;
        while (true)
        {
            Console.Write(prompt);
            input = Console.ReadLine() ?? "";

            if (validator(input))
            {
                return input;
            }
            Console.WriteLine("Nieprawidlowe dane! Sprobuj ponownie.");
        }
    }
}