using System.Collections.Generic;
using System.Runtime.InteropServices.WindowsRuntime;
using AI.SteeringBehaviors.Core;

namespace AI.SteeringBehaviors.StudentAI
{
    public class Flock
    {
        public float AlignmentStrength { get; set; }
        public float CohesionStrength { get; set; }
        public float SeparationStrength { get; set; }
        public List<MovingObject> Boids { get; protected set; }
        public Vector3 AveragePosition { get; set; }
        protected Vector3 AverageForward { get; set; }
        public float FlockRadius { get; set; }

        #region TODO
        public virtual void Update(float deltaTime)
        {
            // calculate avg forward and position
            CalcAvgFor();
            CalcAvgPos();

            //Do more things
            for (int i = 0; i < Boids.Count; i++)
            {
                Vector3 accel = CalcAlignmentAccel(Boids[i]);
                accel += CalcCohesion(Boids[i]);
                accel += CalcSeperation(Boids[i]);
                accel *= Boids[i].MaxSpeed * deltaTime;

                Boids[i].Velocity += accel;

                if (Boids[i].Velocity.Length > Boids[i].MaxSpeed)
                {
                    Boids[i].Velocity.Normalize();
                    Boids[i].Velocity *= Boids[i].MaxSpeed;
                }
                Boids[i].Update(deltaTime);
            }
        }
        #endregion
        public Flock() { 
            
        }

        private void CalcAvgPos()
        {
            Vector3 sum = new Vector3(0, 0, 0);

            for (int i = 0;i < Boids.Count;i++)
            {
                sum += Boids[i].Position;
            }

            sum /= Boids.Count;

            AveragePosition = sum;
        }

        private void CalcAvgFor()
        {
            Vector3 sum = new Vector3(0, 0, 0);

            for (int i = 0; i < Boids.Count; i++)
            {
                sum += Boids[i].Velocity;
            }

            sum /= Boids.Count;

            AverageForward = sum;
        }
        
        private Vector3 CalcAlignmentAccel(MovingObject boid)
        {
            Vector3 change = this.AverageForward / boid.MaxSpeed;
            if (change.Length > 1)
            {
                change.Normalize(); //May need changes, normalize "to max speed"? ************************
            }
            return change * this.AlignmentStrength;
        }

        private Vector3 CalcCohesion(MovingObject boid)
        {
            Vector3 change = this.AveragePosition - boid.Position;
            float dist = change.Length;
            change.Normalize();

            if(dist < this.FlockRadius)
            {
                change *= dist / this.FlockRadius;
            }
            return change * this.CohesionStrength;
        }

        private Vector3 CalcSeperation(MovingObject boid)
        {
            Vector3 sum = new Vector3(0,0,0);

            for(int i = 0; i < Boids.Count; i++)
            {
                if(Boids[i] != boid)
                {
                    Vector3 vec = boid.Position - Boids[i].Position;
                    float dist = vec.Length;

                    if(dist < boid.SafeRadius)
                    {
                        vec.Normalize();
                        vec *= (boid.SafeRadius - dist) / boid.SafeRadius;
                        sum += vec;
                    }
                }
            }
            if(sum.Length < 1.0f)
            {
                sum.Normalize();
            }
            return sum * this.SeparationStrength;
        }
    }
}
