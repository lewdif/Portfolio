using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class Test : MonoBehaviour
{
    RestClient rc = null;
    public Button btnOK;
    bool isSuccess;

    public InputField IDInputField;
    public InputField PWInputField;

    void Start()
    {
        HideErrImg();

        isSuccess = false;
        rc = RestClient.Instance;

        btnOK.onClick.AddListener(() =>
        {
            Debug.Log(IDInputField.text);
            Debug.Log(PWInputField.text);

            rc.Request("login.php", "post", (response) => {

                if (response["error"].Value != "no")
                {
                    ShowErrImg();
                    return;
                }

                print("login res: " + response["error"].Value);
                isSuccess = true;

            }, new Dictionary<string, string>() { { "userid", IDInputField.text }, { "password", PWInputField.text } });

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
}