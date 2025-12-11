using UnityEngine;

public class AudioManager : MonoBehaviour
{
    public static AudioManager Instance;
    
    [Header("Audio Clips")]
    public AudioClip coinSound;
    public AudioClip ballLandSound;
    public AudioClip jumpSound;
    
    private AudioSource audioSource;
    
    void Awake()
    {
        if (Instance == null)
            Instance = this;
        else
            Destroy(gameObject);
            
        audioSource = gameObject.AddComponent<AudioSource>();
    }
    
    public void PlayCoinSound()
    {
        audioSource.PlayOneShot(coinSound);
    }
    
    public void PlayBallLandSound()
    {
        audioSource.PlayOneShot(ballLandSound);
    }
    
    public void PlayJumpSound()
    {
        audioSource.PlayOneShot(jumpSound);
    }
}