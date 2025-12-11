using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    public static GameManager Instance;

    [Header("Game Settings")]
    public int coinsToWin = 10;
    public float gameTime = 180f;

    [Header("UI References")]
    public GameObject startMenuUI;
    public GameObject gameUI;
    public GameObject gameOverUI;
    public GameObject gameClearUI;
    public TMPro.TextMeshProUGUI timerText;
    public TMPro.TextMeshProUGUI coinText;
    public TMPro.TextMeshProUGUI gameOverText;
    public TMPro.TextMeshProUGUI gameClearText;

    private int coinsCollected = 0;
    private float currentTime;
    private bool isGameActive = false;
    private bool isGameOver = false;

    void Awake()
    {
        if (Instance == null)
            Instance = this;
        else
            Destroy(gameObject);
    }

    void Start()
    {
        ShowStartMenu();
    }

    void Update()
    {
        if (isGameActive && !isGameOver)
        {
            currentTime -= Time.deltaTime;
            UpdateTimerUI();

            if (currentTime <= 0)
            {
                GameOver();
            }
        }
    }

    public void StartGame()
    {
        startMenuUI.SetActive(false);
        gameUI.SetActive(true);
        gameOverUI.SetActive(false);
        gameClearUI.SetActive(false);

        coinsCollected = 0;
        currentTime = gameTime;
        isGameActive = true;
        isGameOver = false;

        UpdateCoinUI();
        UpdateTimerUI();

        FindObjectOfType<SpawnManager>()?.SpawnAll();
        
        BallSpawner ballSpawner = FindObjectOfType<BallSpawner>();
        if (ballSpawner != null)
        {
            ballSpawner.StartSpawning();
        }
    }

    public void ShowStartMenu()
    {
        startMenuUI.SetActive(true);
        gameUI.SetActive(false);
        gameOverUI.SetActive(false);
        gameClearUI.SetActive(false);
        isGameActive = false;
    }

    public void CollectCoin()
    {
        coinsCollected++;
        UpdateCoinUI();

        if (coinsCollected >= coinsToWin)
        {
            GameClear();
        }
    }

    void UpdateCoinUI()
    {
        coinText.text = $"Coins: {coinsCollected}/{coinsToWin}";
    }

    void UpdateTimerUI()
    {
        int minutes = Mathf.FloorToInt(currentTime / 60);
        int seconds = Mathf.FloorToInt(currentTime % 60);
        timerText.text = $"{minutes:00}:{seconds:00}";
    }

    void GameClear()
    {
        isGameOver = true;
        isGameActive = false;
        gameUI.SetActive(false);
        gameClearUI.SetActive(true);
        gameClearText.text = "GAME CLEAR!";
        
        BallSpawner spawner = FindObjectOfType<BallSpawner>();
        if (spawner != null)
        {
            spawner.StopSpawning();
        }
        
        Time.timeScale = 0f;
    }

    public void GameOver()
    {
        if (isGameOver) return;
        
        isGameOver = true;
        isGameActive = false;
        gameUI.SetActive(false);
        gameOverUI.SetActive(true);
        gameOverText.text = "GAME OVER";
        
        BallSpawner spawner = FindObjectOfType<BallSpawner>();
        if (spawner != null)
        {
            spawner.StopSpawning();
        }
        
        Time.timeScale = 0f;
    }

    public void RestartGame()
    {
        Time.timeScale = 1f;
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
    }

    public void QuitGame()
    {
        Application.Quit();
    }
}