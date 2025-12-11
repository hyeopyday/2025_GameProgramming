using UnityEngine;

public class BallSpawner : MonoBehaviour
{
    public GameObject ballPrefab;
    public float spawnInterval = 1f;
    public float spawnHeight = 20f;
    public float spawnAreaSize = 40f;
    
    private float spawnTimer = 0f;
    private bool isSpawning = false;
    
    void Update()
    {
        if (!isSpawning) return;
        
        spawnTimer += Time.deltaTime;
        
        if (spawnTimer >= spawnInterval)
        {
            SpawnBall();
            spawnTimer = 0f;
        }
    }
    
    public void StartSpawning()
    {
        isSpawning = true;
        spawnTimer = 0f;
    }
    
    public void StopSpawning()
    {
        isSpawning = false;
    }
    
    void SpawnBall()
    {
        Vector3 randomPos = new Vector3(
            Random.Range(-spawnAreaSize / 2, spawnAreaSize / 2),
            spawnHeight,
            Random.Range(-spawnAreaSize / 2, spawnAreaSize / 2)
        );
        
        Instantiate(ballPrefab, randomPos, Quaternion.identity);
    }
}