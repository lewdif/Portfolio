using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterControl : MonoBehaviour
{
    public GameObject MonsterPrefab = null;

    public static float RESPAWN_TIME_MONSTER = 20.0f;

    private float respawnTimerMonster = 0.0f;

    private float maxVal;
    private float subVal;
    public float step_timer = 0.0f; // 타이머.

    void Start ()
    {
        maxVal = 0.0f;
	}

	void Update ()
    {
        step_timer += Time.deltaTime;
        respawnTimerMonster += Time.deltaTime;

        if (GameObject.Find("GameRoot").GetComponent<GameStatus>().campFire < 0.3f)
        {
            maxVal = 5.0f;
        }
        else if (GameObject.Find("GameRoot").GetComponent<GameStatus>().campFire >= 0.3f
            && GameObject.Find("GameRoot").GetComponent<GameStatus>().campFire < 0.7f)
        {
            maxVal = 2.5f;
        }
        else
        {
            maxVal = 0.0f;
        }

        if(step_timer > 45.0f && step_timer < 80.0f)
        {
            subVal = 4.0f;
        }
        else if (step_timer >= 80.0f && step_timer < 120.0f)
        {
            subVal = 8.0f;
        }
        else if (step_timer >= 120.0f)
        {
            subVal = 10.0f;
        }

        if (respawnTimerMonster > RESPAWN_TIME_MONSTER)
        {
            respawnTimerMonster = Random.Range(0.0f + maxVal + subVal, 5.0f + maxVal + subVal);
            //Debug.Log(respawnTimerMonster +", "+ maxVal + ", " + subVal);
            respawnMonster();
        }
	}

    public void respawnMonster()
    {
        GameObject go = GameObject.Instantiate(MonsterPrefab) as GameObject;
        Vector3 pos = new Vector3(Random.Range(-8.5f, 8.5f), 0.5f, Random.Range(-8.5f, 8.5f));
        go.transform.position = pos;
    }
}
