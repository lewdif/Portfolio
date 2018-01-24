using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class loginTest : MonoBehaviour
{
    public Button btnOK;
    bool isSuccess;

    // InputField 맴버변수 
    public InputField idInputField;
    public InputField pwInputField;

    void Start()
    {
        HideErrImg();

        isSuccess = false;

        btnOK.onClick.AddListener(() =>
        {
            logtest();
            Debug.Log(idInputField.text);
            Debug.Log(pwInputField.text);
        });
    }

    void Update()
    {
        if (isSuccess.Equals(true))
        {
            SceneManager.LoadScene("001");
        }
    }

    private void HideErrImg()
    {
        GameObject.Find("Canvas/LogInWnd/ErrorImg1").GetComponent<Image>().enabled = false;
        GameObject.Find("Canvas/LogInWnd/ErrorImg2").GetComponent<Image>().enabled = false;
    }

    private void ShowErrImg()
    {
        GameObject.Find("Canvas/LogInWnd/ErrorImg1").GetComponent<Image>().enabled = true;
        GameObject.Find("Canvas/LogInWnd/ErrorImg2").GetComponent<Image>().enabled = true;
    }

    // 코루틴 시작
    public void logtest()
    {
        StartCoroutine(TestLogin());
    }


    IEnumerator TestLogin()
    {
        string url = "http://localhost:8080/login.php";

        // 폼 필드 생성
        WWWForm loginData = new WWWForm();

        //현재_id.text 값을 php의 id_data로 대입
        loginData.AddField("user_id", idInputField.text);
        loginData.AddField("user_pw", pwInputField.text);

        StaticVal.SetName(idInputField.text);

        //폼필드 데이터 전송
        WWW login = new WWW(url, loginData);

        yield return login;

        if (login.text.Contains("FAIL"))
        {
            ShowErrImg();
            print(login.text);
        }
        else
        {
            print(login.text);

            if (login.text.Contains("SUCCESS"))
            {
                isSuccess = true;
            }

            login.Dispose(); //clear our form in game
        }

    }
}
