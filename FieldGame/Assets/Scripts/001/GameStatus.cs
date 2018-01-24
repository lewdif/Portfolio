using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

public class GameStatus : MonoBehaviour
{
    // 철광석, 식물을 사용했을 때 각각의 수리 정도.
    public static float GAIN_FIRE_WOOD = 0.10f;

    // 사과, 식물을 먹었을 때 각각의 체력 회복 정도.
    public static float REGAIN_SATIETY_FOOD = 0.7f;
    public float campFire = 1.0f; // 우주선의 수리 정도(0.0f~1.0f).
    public float satiety = 1.0f; // 배고픔,체력(0.0f~1.0f).
    public static float CONSUME_SATIETY_ALWAYS = 0.025f;
    public static float CONSUME_FIRE_ALWAYS = 0.018f;

    void Start()
    {

    }

    void Update()
    {
        GameObject.Find("Canvas/Stamina").GetComponent<Text>().text = (satiety * 100f).ToString("N0") + "%";
        GameObject.Find("Canvas/Fire").GetComponent<Text>().text = (campFire * 100f).ToString("N0") + "%";

        if (satiety <= 0.0f)
        {
            GameObject.Find("GameRoot").GetComponent<ItemRoot>().ShootingCtrl(true);
        }
        else
        {
            GameObject.Find("GameRoot").GetComponent<ItemRoot>().ShootingCtrl(false);
        }
    }

    // 우주선 수리를 진행
    public void addFire(float add)
    {
        campFire = Mathf.Clamp01(campFire + add); // 0.0~1.0 강제 지정
    }

    // 체력을 늘리거나 줄임
    public void addSatiety(float add)
    {
        satiety = Mathf.Clamp01(satiety + add);
    }

    // 게임이 끝났는지 검사
    public bool isGameOver()
    {
        bool is_over = false;
        if (campFire <= 0.0f)
        { // 체력이 0이하라면.
            is_over = true; // 게임 오버.
        }
        return (is_over);
    }

    // 배를 고프게 하는 메서드 추가
    public void alwaysSatiety()
    {
        satiety = Mathf.Clamp01(satiety - CONSUME_SATIETY_ALWAYS * Time.deltaTime);
    }

    public void alwaysFire()
    {
        campFire = Mathf.Clamp01(campFire - CONSUME_FIRE_ALWAYS * Time.deltaTime);
    }
}
