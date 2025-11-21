using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;

public class GameResult : MonoBehaviour
{
    private int highScore;
    public TextMeshProUGUI resultTime;
    public TextMeshProUGUI bestTime;
    public GameObject parts;

    void Start()
    {
        if (PlayerPrefs.HasKey("HighScore"))
        {
            highScore = PlayerPrefs.GetInt("HighScore");
        }
        else
        {
            highScore = 999;
        }
    }

    void Update()
    {
        if (GoalArea.goal)
        {
            parts.SetActive(true);

            int result = Mathf.FloorToInt(Timer.time);
            resultTime.text = "ResultTime " + result;
            bestTime.text = "BestTime " + highScore;

            if (highScore > result)
            {
                highScore = result;                // 로컬 값도 갱신해줘야 다음 프레임에 바로 반영됨
                PlayerPrefs.SetInt("HighScore", result);
                PlayerPrefs.Save();
            }
        }
    }

    public void OnRetry()
    {
        SceneManager.LoadScene("Main");
    }
}
