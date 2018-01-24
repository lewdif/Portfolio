using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class ShipAlert : MonoBehaviour
{
    private AudioSource hornSound;
    public AudioClip Horn;

    private float passedTime;
    private float resqueTime;
    private float alertTime;
    private float randomVal;
    private bool isShipNear;
    private bool isShipHere;
    private GameStatus status;
    public float step_timer = 0.0f; // 타이머.

    void Start()
    {
        initAll();

        hornSound = this.gameObject.AddComponent<AudioSource>();
        hornSound.clip = Horn;
        hornSound.loop = false;

        initCnt();

        status = GameObject.Find("GameRoot").GetComponent<GameStatus>();
    }

    void Update()
    {
        randomVal = Random.Range(0.0f, 10.0f);
        step_timer += Time.deltaTime;

        if (isShipNear == false)
        {
            passedTime += Time.deltaTime;
        }

        if (passedTime > randomVal + 40)
        {
            isShipNear = true;
            GameObject.Find("Canvas/Alert/ExplanationMark1").GetComponent<Image>().enabled = true;
            GameObject.Find("Canvas/Alert/ExplanationMark2").GetComponent<Image>().enabled = true;
            
            hornSound.Play();

             passedTime = 0;
        }

        if(isShipNear == true)
        {
            alertTime += Time.deltaTime;
            showCnt(alertTime);
        }

        if (alertTime > 10.0f)
        {
            isShipHere = true;
        }

        if (isShipHere == true)
        {
            GameObject.Find("Canvas/Alert/ExplanationMark1").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/Alert/ExplanationMark2").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/Anchor").GetComponent<Image>().enabled = true;
            resqueTime += Time.deltaTime;
            showCnt(resqueTime);

            if (status.campFire <= 0.85f)
            {
                initAll();
            }
        }

        if(resqueTime >= 10f && status.campFire >= 0.85f)
        {
            StaticVal.SetScore((int)step_timer);
            SceneManager.LoadScene("003");
        }
        /*Debug.Log("Passed Time : " + passedTime);
        Debug.Log("Alert Time : " + alertTime);
        Debug.Log("Resque Time : " + resqueTime);*/
    }

    private void initAll()
    {
        GameObject.Find("Canvas/Anchor").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/Alert/ExplanationMark1").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/Alert/ExplanationMark2").GetComponent<Image>().enabled = false;
        passedTime = 0;
        resqueTime = 0;
        alertTime = 0;
        isShipNear = false;
        isShipHere = false;
        initCnt();
    }

    private void initCnt()
    {
        GameObject.Find("Canvas/10").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/09").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/08").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/07").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/06").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/05").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/04").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/03").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/02").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/01").GetComponent<Image>().enabled = false;
    }

    private void showCnt(float time)
    {
        if (time >= 9)
        {
            GameObject.Find("Canvas/10").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/09").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/08").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/07").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/06").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/05").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/04").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/03").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/02").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/01").GetComponent<Image>().enabled = true;
        }
        else if (time < 9 && time >= 8)
        {
            GameObject.Find("Canvas/10").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/09").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/08").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/07").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/06").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/05").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/04").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/03").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/02").GetComponent<Image>().enabled = true;
            GameObject.Find("Canvas/01").GetComponent<Image>().enabled = false;
        }
        else if (time < 8 && time >= 7)
        {
            GameObject.Find("Canvas/10").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/09").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/08").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/07").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/06").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/05").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/04").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/03").GetComponent<Image>().enabled = true;
            GameObject.Find("Canvas/02").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/01").GetComponent<Image>().enabled = false;
        }
        else if (time < 7 && time >= 6)
        {
            GameObject.Find("Canvas/10").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/09").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/08").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/07").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/06").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/05").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/04").GetComponent<Image>().enabled = true;
            GameObject.Find("Canvas/03").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/02").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/01").GetComponent<Image>().enabled = false;
        }
        else if (time < 6 && time >= 5)
        {
            GameObject.Find("Canvas/10").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/09").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/08").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/07").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/06").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/05").GetComponent<Image>().enabled = true;
            GameObject.Find("Canvas/04").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/03").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/02").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/01").GetComponent<Image>().enabled = false;
        }
        else if (time < 5 && time >= 4)
        {
            GameObject.Find("Canvas/10").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/09").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/08").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/07").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/06").GetComponent<Image>().enabled = true;
            GameObject.Find("Canvas/05").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/04").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/03").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/02").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/01").GetComponent<Image>().enabled = false;
        }
        else if (time < 4 && time >= 3)
        {
            GameObject.Find("Canvas/10").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/09").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/08").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/07").GetComponent<Image>().enabled = true;
            GameObject.Find("Canvas/06").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/05").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/04").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/03").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/02").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/01").GetComponent<Image>().enabled = false;
        }
        else if (time < 3 && time >= 2)
        {
            GameObject.Find("Canvas/10").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/09").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/08").GetComponent<Image>().enabled = true;
            GameObject.Find("Canvas/07").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/06").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/05").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/04").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/03").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/02").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/01").GetComponent<Image>().enabled = false;
        }
        else if (time < 2 && time >= 1)
        {
            GameObject.Find("Canvas/10").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/09").GetComponent<Image>().enabled = true;
            GameObject.Find("Canvas/08").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/07").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/06").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/05").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/04").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/03").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/02").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/01").GetComponent<Image>().enabled = false;
        }
        else if (time < 1 && time > 0)
        {
            GameObject.Find("Canvas/10").GetComponent<Image>().enabled = true;
            GameObject.Find("Canvas/09").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/08").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/07").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/06").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/05").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/04").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/03").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/02").GetComponent<Image>().enabled = false;
            GameObject.Find("Canvas/01").GetComponent<Image>().enabled = false;
        }
    }
}