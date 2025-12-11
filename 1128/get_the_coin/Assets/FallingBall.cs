using UnityEngine;

public class FallingBall : MonoBehaviour
{
    private bool hasHitPlayer = false;
    
   void OnCollisionEnter(Collision collision)
{
    if (collision.gameObject.CompareTag("Ground"))
    {
        AudioManager.Instance.PlayBallLandSound();
        Destroy(gameObject, 0.5f);
    }
    
    if (!hasHitPlayer && collision.gameObject.CompareTag("Player"))
    {
        hasHitPlayer = true;
        GameManager.Instance.GameOver();
        Destroy(gameObject);
    }
}
}