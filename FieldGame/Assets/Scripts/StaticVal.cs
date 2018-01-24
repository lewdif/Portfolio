using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class StaticVal
{
    public static int SCORE;
    public static string NAME;

    public static void SetName(string name)
    {
        NAME = name;
    }

    public static void SetScore(int num)
    {
        SCORE = num;
    }
}