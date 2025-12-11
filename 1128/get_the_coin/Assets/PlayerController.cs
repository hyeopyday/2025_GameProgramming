using UnityEngine;

[RequireComponent(typeof(CharacterController))]
public class PlayerController : MonoBehaviour
{
    [Header("Movement")]
    public float moveSpeed = 5f;
    public float jumpForce = 8f;
    public float gravity = -20f;

    [Header("Camera")]
    public Transform cameraTransform;
    public Vector3 cameraOffset = new Vector3(0, 3, -5);
    public float cameraSmooth = 5f;

    private CharacterController controller;
    private Vector3 velocity;
    private bool isGrounded;
    private Animator animator;

    void Start()
    {
        controller = GetComponent<CharacterController>();
        animator = GetComponent<Animator>();
        
        if (cameraTransform == null)
        {
            cameraTransform = Camera.main.transform;
        }
    }

    void Update()
    {
        isGrounded = controller.isGrounded;

        if (isGrounded && velocity.y < 0)
        {
            velocity.y = -2f;
        }

        float horizontal = Input.GetAxis("Horizontal");
        float vertical = Input.GetAxis("Vertical");

        Vector3 cameraForward = cameraTransform.forward;
        cameraForward.y = 0;
        cameraForward.Normalize();

        Vector3 cameraRight = cameraTransform.right;
        cameraRight.y = 0;
        cameraRight.Normalize();

        Vector3 move = cameraRight * horizontal + cameraForward * vertical;
        
        float inputMagnitude = move.magnitude;
        if (inputMagnitude > 0.1f)
        {
            controller.Move(move.normalized * moveSpeed * Time.deltaTime);
            
            Quaternion targetRotation = Quaternion.LookRotation(move);
            transform.rotation = Quaternion.Slerp(transform.rotation, targetRotation, 10f * Time.deltaTime);
        }

        if (Input.GetButtonDown("Jump") && isGrounded)
        {
            velocity.y = Mathf.Sqrt(jumpForce * -2f * gravity);
            AudioManager.Instance.PlayJumpSound();
        }
        velocity.y += gravity * Time.deltaTime;
        controller.Move(velocity * Time.deltaTime);

        UpdateCameraPosition();
        UpdateAnimation(inputMagnitude);
    }

    void UpdateAnimation(float speed)
    {
        if (animator != null)
        {
            animator.SetFloat("MoveSpeed", speed);
            animator.SetBool("Grounded", isGrounded);
        }
    }

    void UpdateCameraPosition()
    {
        if (cameraTransform != null)
        {
            Vector3 desiredPosition = transform.position + transform.TransformDirection(cameraOffset);
            cameraTransform.position = Vector3.Lerp(cameraTransform.position, desiredPosition, cameraSmooth * Time.deltaTime);
            
            Vector3 lookTarget = transform.position + Vector3.up * 1.5f;
            Quaternion targetRotation = Quaternion.LookRotation(lookTarget - cameraTransform.position);
            cameraTransform.rotation = Quaternion.Slerp(cameraTransform.rotation, targetRotation, cameraSmooth * Time.deltaTime);
        }
    }

    void OnTriggerEnter(Collider other)
{
    if (other.CompareTag("Coin"))
    {
        AudioManager.Instance.PlayCoinSound();
        GameManager.Instance.CollectCoin();
        Destroy(other.gameObject);
    }
}
}