using UnityEngine;
using System.Collections.Generic;

public class SpawnManager : MonoBehaviour
{
    [Header("Prefabs")]
    public GameObject playerPrefab;
    public GameObject coinPrefab;

    [Header("Spawn Settings")]
    public int coinCount = 15;
    public float spawnAreaSize = 50f;

    [Header("Ground Layer")]
    public LayerMask groundLayer;
    public float groundCheckHeight = 100f;

    private List<Vector3> spawnedPositions = new List<Vector3>();

    public void SpawnAll()
    {
        spawnedPositions.Clear();
        
        SpawnPlayer();
        SpawnCoins();
    }

    void SpawnPlayer()
    {
        Vector3 spawnPos = GetRandomGroundPosition();
        if (spawnPos != Vector3.zero)
        {
            Instantiate(playerPrefab, spawnPos, Quaternion.identity);
            spawnedPositions.Add(spawnPos);
        }
    }

    void SpawnCoins()
    {
        for (int i = 0; i < coinCount; i++)
        {
            Vector3 spawnPos = GetRandomGroundPosition();
            if (spawnPos != Vector3.zero)
            {
                Instantiate(coinPrefab, spawnPos + Vector3.up * 0.5f, Quaternion.identity);
            }
        }
    }

    Vector3 GetRandomGroundPosition()
    {
        for (int i = 0; i < 30; i++)
        {
            Vector3 randomPos = new Vector3(
                Random.Range(-spawnAreaSize, spawnAreaSize),
                groundCheckHeight,
                Random.Range(-spawnAreaSize, spawnAreaSize)
            );

            RaycastHit hit;
            if (Physics.Raycast(randomPos, Vector3.down, out hit, groundCheckHeight * 2, groundLayer))
            {
                return hit.point;
            }
        }
        
        return Vector3.zero;
    }
}