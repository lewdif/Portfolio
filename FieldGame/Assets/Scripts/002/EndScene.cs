using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class EndScene : MonoBehaviour
{
    private Button toTitle;
    RestClient rc = null;

    void Start()
    {
        rc = RestClient.Instance;
        toTitle = GameObject.Find("Canvas/Button").GetComponent<Button>();
        
        toTitle.onClick.AddListener(() => {

            rc.Request("logout.php", "post", (response) => {

                if (response["error"].Value != "no") return;

                print("logout res: " + response["error"].Value);

            });

            SceneManager.LoadScene("000");
        });
    }
}
