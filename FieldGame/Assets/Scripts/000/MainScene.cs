using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class MainScene : MonoBehaviour
{
    private Button btnStart;
    private Button btnQuit;
    private Button btnHTP;
    private Button btnReturn;
    private Button btnCancle;
    
    private bool isHTP_on;

    void Start ()
    {
        initHTP();
        hideLogInWnd();
        isHTP_on = false;

        btnStart = GameObject.Find("Canvas/Start").GetComponent<Button>();
        btnQuit = GameObject.Find("Canvas/Quit").GetComponent<Button>();
        btnHTP = GameObject.Find("Canvas/HTP").GetComponent<Button>();
        btnReturn = GameObject.Find("Canvas/HowToPlay/Return").GetComponent<Button>();
        btnCancle = GameObject.Find("Canvas/LogInWnd/Cancle").GetComponent<Button>();

        btnStart.onClick.AddListener(() =>
        {
            showLogInWnd();

            //SceneManager.LoadScene("001");
        });

        btnQuit.onClick.AddListener(() =>
        {
            Application.Quit();
        });

        btnHTP.onClick.AddListener(() =>
        {
            setHTP();
            //isHTP_on = true;
        });

        btnReturn.onClick.AddListener(() =>
        {
            initHTP();
        });

        btnCancle.onClick.AddListener(() =>
        {
            hideLogInWnd();
        });
        //if (isHTP_on == true && Input.GetMouseButtonDown(0))
        //{
        //    initHTP();
        //    isHTP_on = false;
        //}
    }

    void initHTP()
    {
        GameObject.Find("Canvas/HowToPlay").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/HowToPlay/00").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/HowToPlay/01").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/HowToPlay/02").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/HowToPlay/03").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/HowToPlay/04").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/HowToPlay/05").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/HowToPlay/06").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/HowToPlay/07").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/HowToPlay/08").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/HowToPlay/09").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/HowToPlay/10").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/HowToPlay/Return").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/HowToPlay/Return/Text").GetComponent<Text>().enabled = false;
    }

    void setHTP()
    {
        GameObject.Find("Canvas/HowToPlay").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/HowToPlay/00").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/HowToPlay/01").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/HowToPlay/02").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/HowToPlay/03").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/HowToPlay/04").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/HowToPlay/05").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/HowToPlay/06").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/HowToPlay/07").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/HowToPlay/08").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/HowToPlay/09").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/HowToPlay/10").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/HowToPlay/Return").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/HowToPlay/Return/Text").GetComponent<Text>().enabled = true;
    }

    private void hideLogInWnd()
    {
        GameObject.Find("Canvas/LogInWnd").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/LogInWnd/LogInMain").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/LogInWnd/IDImage").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/LogInWnd/PWImage").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/LogInWnd/OK").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/LogInWnd/Cancle").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/LogInWnd/ErrorImg1").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/LogInWnd/ErrorImg2").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/LogInWnd/IDInputField/Placeholder").SetActive(false);
        GameObject.Find("Canvas/LogInWnd/IDInputField/Text").SetActive(false);
        GameObject.Find("Canvas/LogInWnd/IDInputField").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/LogInWnd/PWInputField/Placeholder").SetActive(false);
        GameObject.Find("Canvas/LogInWnd/PWInputField/Text").SetActive(false);
        GameObject.Find("Canvas/LogInWnd/PWInputField").GetComponent<Image>().enabled = false;
    }

    private void showLogInWnd()
    {
        GameObject.Find("Canvas/LogInWnd").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/LogInWnd/LogInMain").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/LogInWnd/IDImage").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/LogInWnd/PWImage").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/LogInWnd/OK").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/LogInWnd/Cancle").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/LogInWnd/IDInputField").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/LogInWnd/IDInputField/Placeholder").SetActive(true);
        GameObject.Find("Canvas/LogInWnd/IDInputField/Text").SetActive(true);
        GameObject.Find("Canvas/LogInWnd/PWInputField").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/LogInWnd/PWInputField/Placeholder").SetActive(true);
        GameObject.Find("Canvas/LogInWnd/PWInputField/Text").SetActive(true);
    }
}
